# el_simp_compiler
- [x] Lexer
- [ ] Compiler

* Line Types
  * Not Founded
  * Empty
  * Variable Define
  * Function Define
  * Setting Variable

The language lexer controls really looks like a python language. Example functions.
#### Functions
This is example function define:
```python
def function():
  end
```
But unlike the python language you can define a in-object function. Example:
```python
variable = "hello world"
def variable.onCreate():
  style = "color:gray;"
  end
```
And that language has a lot of private functions for html.
##### onCreate()
This function runs at creating the program. So you can use that for changing style or setting start variables.
##### onClick()
You can use this for buttons. If the object have that function, this object will be create as a button or 
```HTML 
<a>
```
##### idhJava()
That function will be run once when browser not support javascript.

#### Variables
There is 3 example of variable define
```python
header = HTML("Hello World","color:white;")
style = "background-color:black;"
counter = 0
```

And that language has a lot of private variable too for html.
##### style
If you define style in source code that will be style of page.
Or if you define a style in onCreate() that will be style of private function.
So there is a example.
```python
// Style of page
style = "background-color:black;"
justtext = HTML("Hello World")
justtext.onCreate() :
  // Style of justtext object
  style = "backgorund-color:red; color:white;"
  end
```

Here the Example code and code's compile result

### Code
```python
// setting title of page
title = HTML("My Page")
// Creating a text object
justtext = HTML("Click 'Click Me' button")
// Creating a button object
button = HTML("Click Me")
// Creating a onClick function. If any object have that function that object will be created as <a> or <button>
def button.onClick() :
 justtext="Hell yeah" // Setting justttext's text "Hell Yeah" if clicked that object
 end
```
### Result
```html
<HTML>
 <head>
  <title>My Page</title>
  <script>
   button_onClick()
   {document.getElementById("button").text = "Hell Yeah";}
  </script>
 </head>
 <body>
  <p id="justtext">Click 'Click Me' button</p>
  <a onclick="button_onClick()" id="button">Click Me</a>
 </body>
<HTML>
```
