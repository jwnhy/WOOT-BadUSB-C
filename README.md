# cs315_bankrobber 

S&P WOOT Workshop
https://www.ieee-security.org/TC/SP2021/SPW2021/WOOT21/  

## Submission Requirements
Due to the short review timeframe, we will require an abstract registration this year. Abstract registration allows the reviewers to bid on the papers they are interested in and allows the authors to continue finalizing the paper until the paper submission deadline. When submitting, make sure to put in a descriptive abstract.  

Abstract registration deadline: Wednesday, January 27, 2021, 11:59 AoE (Anywhere on Earth)  
Paper submission deadline: Friday, January 29, 2021, 11:59 AoE (Anywhere on Earth)  
Notification date: Monday, March 01, 2021  
Workshop date: Thursday, May 27, 2021   

## What to Submit
Submissions must be in PDF format. Papers should be succinct but thorough in presenting the work. The contribution needs to be well motivated, clearly exposed, and compared to the state of the art. Typical research papers are at least 4 pages, and maximum 10 pages long (not counting bibliography and appendix). Yet, papers whose lengths are incommensurate with their contributions will be rejected.

The submission should be formatted in 2-columns, using 10-point Times Roman type on 12-point leading, in a text block of 6.5” x 9”. Please number the pages. Authors must use the IEEE templates.

Note that paper format rules may be clarified. Stay tuned.

## $\LaTeX$ Convention

1. All figures are stored in `./Figs/`, the filename is lower cased and inside $\LaTeX$ they should be labelled with the filename. For example

   ```latex
   \begin{figure}[htbp]
   \includegraphics[width=\linewidth]{./Figs/workflow.png}
   \caption{Workflow of BadUSB-C}
   \label{workflow}
   \end{figure}
   ```

2. Each section should be labeled with their lower cased section name.

   ```latex
   \section{Experiment}
   \label{section:experiment}
   ```