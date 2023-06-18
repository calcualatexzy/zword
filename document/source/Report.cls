\LoadClass{ctexart}
%宏包
\RequirePackage{xeCJK}
\RequirePackage{graphicx}
\RequirePackage{geometry}
\RequirePackage{zhnumber}
\RequirePackage{titlesec}
\RequirePackage{fancyhdr}
\RequirePackage{enumitem}
\RequirePackage{listings}
\RequirePackage{xcolor}
\RequirePackage{array}
% \RequirePackage{mathtools}
\RequirePackage{float}
\RequirePackage{indentfirst}
\RequirePackage{zhnumber}
\RequirePackage{multirow}
% \RequirePackage{subfigure}
\RequirePackage{listings}
\RequirePackage{lmodern}
\RequirePackage{amssymb}
\RequirePackage{ulem}
\RequirePackage{accsupp}
\RequirePackage{diagbox}
\RequirePackage{unicode-math}
\RequirePackage{extarrows}
\RequirePackage{caption}
\RequirePackage{subcaption}
\RequirePackage{multicol}
\RequirePackage{supertabular}
\RequirePackage{algorithm}
\RequirePackage{algpseudocode}
\RequirePackage{amsmath}
\RequirePackage{wrapfig}
\RequirePackage{titletoc}
\RequirePackage{tikz}
% \RequirePackage{pgfplots}
\RequirePackage[hidelinks]{hyperref}

\usetikzlibrary{positioning,arrows.meta,quotes}
\usetikzlibrary{shapes}
\usetikzlibrary{bayesnet}
\usetikzlibrary{decorations.pathreplacing}
\tikzset{>=stealth}
\definecolor{light_red}{RGB}{209,105,81}
\definecolor{light_green}{RGB}{58,181,75}
\definecolor{light_blue}{RGB}{0,153,228}

\setlength{\headheight}{15pt}

\hypersetup{
  colorlinks=true,%打开颜色显示
  linkcolor=light_blue,%内部链接
  filecolor=magenta,%本地连接
  urlcolor=cyan,%网页链接
  % pdftitle={Overleaf Example},
  % pdfpagemode=FullScreen,
}

% 宏定义命令
	% 复制代码不带行号
	\newcommand{\emptyaccsupp}[1]{\BeginAccSupp{ActualText={}}#1\EndAccSupp{}}
	%标红
	\newcommand{\hl}[1]{\textcolor{light_red}{#1}}
	% 定义°为\degree 不需要$, \deg 需要$
	\def\deg{^{\circ}}
	\def\degree{${}^{\circ}$}
	% 在外部打上tikz标记, 在tikz中加上 overlay 可与之互动. \tikzmark[颜色]{名字}{具体文字} 
	\newcommand{\tikzmark}[3][] {\tikz[remember picture, baseline] \node [anchor=base,#1](#2) {#3};}
  % 下划线定义
  \def\zjuu[#1]#2{\underline{\hbox to #1{\hfil#2\hfil}}}
%

% 自定义信息参数传递
  % \newcommand\major[1]{\def\@major{#1}}
  \newcommand\name[1]{\def\@name{#1}}
  \newcommand\std[1]{\def\@std{#1}}
  \newcommand\stdd[1]{\def\@stdd{#1}}
  \newcommand\stddd[1]{\def\@stddd{#1}}
  % \newcommand\stuid[1]{\def\@stuid{#1}}
  % \newcommand\college[1]{\def\@college{#1}}
  \renewcommand\date[1]{\def\@date{#1}}
  % \newcommand\lab[1]{\def\@lab{#1}}
  \newcommand\course[1]{\def\@course{#1}}
  \newcommand\instructor[1]{\def\@instructor{#1}}
  % \newcommand\grades[1]{\def\@grades{#1}}
  \newcommand\expname[1]{\def\@expname{#1}}
  % \newcommand\exptype[1]{\def\@exptype{#1}}
  % \newcommand\tutor[1]{\def\@tutor{#1}}
  % \newcommand\email[1]{\def\@email{#1}}
  % \newcommand\phone[1]{\def\@phone{#1}}
  % \newcommand\qq[1]{\def\@qq{#1}}
%

% 页面参数
  % 行距
  \linespread{1.2}
  % 页边距
  \geometry{top=1in,bottom=1in,left=0.75in,right=0.75in}
  % 目录深度
\setcounter{secnumdepth}{4}
\setcounter{tocdepth}{4}
  % caption距离
  \setlength{\abovecaptionskip}{4pt}
  \setlength{\belowcaptionskip}{4pt}
% 

% 多级标题
%目录居中
\renewcommand*\contentsname{\hfill 目录 \hfill}
%多级标题目录格式
\titlecontents{section}[0pt]{\addvspace{1pc}\bfseries}{\thecontentslabel\quad}{}{\titlerule*[8pt]{$\cdot$}\contentspage}
\titlecontents{subsection}[1em]{\vspace{0.1cm}\normalsize}{\thecontentslabel\quad}{}{\titlerule*[8pt]{$\cdot$}\contentspage}
\titlecontents{subsubsection}[2em]{\vspace{0.1cm}\small}{\thecontentslabel\quad}{}{\titlerule*[8pt]{$\cdot$}\contentspage}
\titlecontents{paragraph}[2em]{\vspace{0.1cm}\small}{\thecontentslabel\quad}{}{\titlerule*[8pt]{$\cdot$}\contentspage}
%多级标题命名格式
\renewcommand\thesection{\Roman{section}}
\renewcommand\thesubsection{\arabic{subsection}.}
\renewcommand\thesubsubsection{\thesubsection\arabic{subsubsection}}
%多级标题字体
\titleformat*{\section}{\large\bfseries}
\titleformat*{\subsection}{\normalsize\bfseries}
\titleformat*{\subsubsection}{\normalsize\slshape}
\titleformat*{\paragraph}{\small\bfseries}
%多级标题间隔
\titlespacing{\section}{0pt}{*1.5}{*1.5}
\titlespacing{\subsection}{2em}{*1}{*1}
\titlespacing{\subsubsection}{2em}{*1}{*1}
\titlespacing{\paragraph}{0pt}{*1}{*1}
%多级序号格式
\setlist[enumerate,1]{label=\arabic*),itemindent=2em,itemsep=0pt,partopsep=0pt,parsep=\parskip,topsep=5pt}
\setlist[enumerate,2]{label=\alph*.,itemindent=1em,itemsep=0pt,partopsep=0pt,parsep=\parskip,topsep=5pt}
\setlist[itemize,1]{itemindent=2em,itemsep=0pt,partopsep=0pt,parsep=\parskip,topsep=5pt}
\setlist[itemize,2]{itemindent=1em,itemsep=0pt,partopsep=0pt,parsep=\parskip,topsep=5pt}
%

% 图片路径（实现多种文件夹都可以放图片
  \graphicspath{{figures/}{figure/}{pictures/}{picture/}{pic/}{pics/}{image/}{images/}}
%

\lstset{
	language=c++,
    basicstyle          =   \normalsize\fontspec{Consolas},          % 基本代码风格
	morekeywords		=	{ll},	%增加高亮
    keywordstyle        =   \color{blue!90},          % 关键字风格
    commentstyle        =   \color{green!40!black!60},  % 注释的风格，斜体
    stringstyle         =   \ttfamily\slshape\color[RGB]{140,81,25},  % 字符串风格
    % framerule           =   2.5em,
	rulesepcolor		=	\color{red!20!green!20!blue!20},%代码块边框为淡青色
	framextopmargin=2pt,framexbottommargin=2pt,abovecaptionskip=-3pt,belowcaptionskip=3pt,%阴影边框设定
	rulecolor           =   \color{gray!10},  
	flexiblecolumns     =   flase,                % 别问为什么，加上这个
    numbers             =   left,   % 行号的位置在左边
    showspaces          =   false,  % 是否显示空格，显示了有点乱，所以不显示了
    numberstyle         =   \footnotesize\fontspec{Consolas}\emptyaccsupp,    % 行号的样式，小五号，tt等宽字体
    showstringspaces    =   false,
    captionpos          =   t,      % 这段代码的名字所呈现的位置，t指的是top上面
    frame               =   shadowbox,   % 显示边框
    tabsize             =   4,
    breaklines          =   true,   % 自动换行，建议不要写太长的行
    breakatwhitespace   =   false,       	% 设置自动中断是否只发生在空格处
    escapeinside        =   ``,     	% 在``里显示中文
    columns             =   fixed,  % 如果不加这一句，字间距就不固定，很丑，必须
    % basewidth           =    0.6em,
    xleftmargin         =    1em,  
    xrightmargin        =    1em,     % 设定listing左右的空白
}

% 页眉
  \pagestyle{fancy}
  \lhead{\small{\@expname}}
  \rhead{\small{\@name}}
% 

% 封面
  \newcommand{\makecover}{
    \begin{center}
      \begin{center}
        \includegraphics[width=0.8\linewidth]{../source/logo/cover.png}
      \end{center}
      \vspace{1cm}
      \bfseries\huge{项目设计说明}\\
      \vspace{0.5cm}
    %   \bfseries\Huge{\@expname}
      \vspace{1.35cm}
      \begin{center}
        \Large
        \linespread{2}
        \centering
        \renewcommand\arraystretch{1.6}
        \begin{tabular}{p{5em}p{12em}}
			\bfseries{课程名称: } & \zjuu[180pt]\@course \\ 
			\bfseries{项\hphantom{两格}目: }     & \zjuu[180pt]\@expname   \\ 
			% \bfseries{组\hphantom{两格}员: }     & \zjuu[180pt]\@name   \\ 
                \bfseries{姓名学号：}     & \zjuu[180pt]\@std  \\ 
                \bfseries{\hphantom{五格的占位}}     & \zjuu[180pt]\@stdd  \\
                \bfseries{\hphantom{五格的占位}}     & \zjuu[180pt]\@stddd  \\
			\bfseries{指导老师: } & \zjuu[180pt]\@instructor  \\ 
        \end{tabular}
      \end{center}
      \vspace{2cm}
      \Large{\@date}
    \end{center}
    \thispagestyle{empty}
    \newpage
  }
% 