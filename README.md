##Image Annotation Tool

This is an image annotation (pixel labelling) tool written in Qt5, which runs in Mac OS, Linux and Window.

This tool/software is useful to prepare the training data for supervised object segmentation problem.

You can just change the imgannotation.json file for the require mask types and corresponding colors. 

## Instructions

* 1: Download Qt at: qt.org
* 2: Add the Qt file into your system PATH
  `PATH=~/Qt/5.9/clang_64/bin:$PATH` and then `EXPORT PATH`
* 3: Run `qmake`
* 4: Run `make all`

The app called ImgAnnotation is then generated after running the above commands.

## How to Use the App

* 1: Click on the top nav bar - select Database, open directory
* 2: Once you have chosen your directory, click open
* 3: You need to add an object under "Object for Image"
* 4: And then you can draw on the images
* 5: Things are automatically saved as mask images with the associated file name: _orig_img_name_.mask.<n>.png


