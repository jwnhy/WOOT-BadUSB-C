const express = require("express");
const app = express();
const port = 3000;
const qr = require("qr-image");
const bwipjs = require("bwip-js");
const bodyParser = require("body-parser");

app.use(bodyParser.urlencoded({ extended: true }));

app.set("views", "./views");
app.set("view engine", "pug");

let img = "";

//引入qr-image module
//生成‘https://leibosite.github.io’信息、png类型的二维码，默认为M

var generatorQrImage = function (qrInfo, qrPath) {
  var qr_svg = qr.image(qrInfo, "H", { type: "png" });
  var qrPa = path.join(__dirname, qrPath);
  qr_svg.pipe(fs.createWriteStream(qrPa));
  fs.exists(qrPa, function (isExist) {
    if (isExist) {
      console.log("generator success!");
    }
    console.log("generator fail");
  });
};

// respond with "hello world" when a GET request is made to the homepage
// app.get("/", function (req, res) {
//   res.render("index", { title: "Hey", message: "Hello there!" });
// });

app.get("/bar", function (req, res) {
  res.sendFile(__dirname + "/bar.png");
});

app.get("/qr", function (req, res) {
  res.sendFile(__dirname + "/qr.png");
});

app.get("/", function (req, res) {
  res.render("index", { title: "Hey", message: "Hello there!" });
});

app.post("/", function (req, res) {
  code = req.body.code;
  img = qr.image(code, { type: "png" });
  console.log(img);
  img.pipe(require("fs").createWriteStream("qr.png"));

  bwipjs.toBuffer(
    {
      bcid: "code128", // Barcode type
      text: code, // Text to encode
      scale: 3, // 3x scaling factor
      height: 10, // Bar height, in millimeters
      includetext: false, // Show human-readable text
      textxalign: "center", // Always good to set this
    },
    function (err, png) {
      if (err) {
        console.log(err);
      } else {
        require("fs").writeFile("bar.png", png, "binary", function (err) {});
        //   console.log(typeof );
        // require("fs").createReadStream(png).pipe(require("fs").createWriteStream("bar.png"));
      }
    }
  );

  res.sendStatus(200);
});

app.listen(port, "0.0.0.0", () => {
  console.log("XD");
});
