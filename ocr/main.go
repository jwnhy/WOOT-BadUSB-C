package main

import (
	"errors"
	"fmt"
	"github.com/gin-gonic/gin"
	"gorm.io/driver/postgres"
	_ "gorm.io/driver/postgres"
	"gorm.io/gorm"
	"net/http"
)

// 统一响应结构体
type Response struct {
	Code    int         `json:"code"`
	Message string      `json:"message"`
	Data    interface{} `json:"data"`
}

var db *gorm.DB

func ping(c *gin.Context) {
	var response Response
	response.Code = 0
	response.Message = "success"
	response.Data = ""
	c.JSON(200, response)
	return
}

var nmd = make(chan *Data, 1000000)

func main() {
	dsn := "host=127.0.0.1 user=postgres password=postgres dbname=armory sslmode=disable"
	var err error
	db, err = gorm.Open(postgres.Open(dsn), &gorm.Config{})
	defer func() {
		wtf, _ := db.DB()
		_ = wtf.Close()
	}()
	if err != nil {
		fmt.Println("connect DB error")
		panic(err)
	}
	db.AutoMigrate(&Model{})

	g := gin.Default() // 这里的接口没有使用权限认证中间件

	api := g.Group("/api")
	api.GET("/ping", ping) // 这个是通用的接口

	api.POST("/data", qwq)

	go cao()

	_ = g.Run("0.0.0.0:8099")
}

type Data struct {
	Number int    `json:"number"`
	Name   string `json:"name"`
	Text   string `json:"text"`
}

type Model struct {
	gorm.Model
	Data
}

func cao() {
	for model := range nmd {
		test := Model{}
		if errors.Is(db.Where("number = ? AND name = ?", model.Number, model.Name).First(&test).Error, gorm.ErrRecordNotFound) {
			fmt.Println("==>", model.Number, model.Name)
			db.Create(&Model{
				Data:  *model,
			})
		}
	}
	fmt.Println("exit")
}

func qwq(c *gin.Context) {

	request := Data{}
	if err := c.ShouldBind(&request); err != nil {
		panic(err)
	}
	nmd <- &request
	c.Status(http.StatusOK)
}
