from tkinter import *
from tkinter import filedialog as fd
from tkinter.messagebox import showinfo
from PIL import ImageTk,Image

gui = Tk()



#Set app window
gui.title('Fingerprint morphing')
gui.geometry('800x800')

#set fileformats for loading input images
def select_files():
    filetypes = (
        ('images', '*.bmp ; *.tiff ; *.jpg ; *.JPEG ; *.png'),
        ('All files', '*.*')
    )

    filenames = fd.askopenfilenames(
        title='Open files',
        initialdir='/',
        filetypes=filetypes)

    showinfo(
        title='Selected Files',
        message=filenames
    )

# open 1st image button
open_button1 = Button(
    gui,
    text='Select first image',
    command=select_files
)
open_button1.pack(expand=True)
open_button1.place(x=25, y=25)

canvas = Canvas(gui, width = 300, height = 300)      
canvas.pack()      
canvas.place(x=25, y=75)
img = ImageTk.PhotoImage(Image.open("result.tif"))  
canvas.create_image(0,0, anchor=NW, image=img)  

# open 2nd image button
open_button2 = Button(
    gui,
    text='Select second image',
    command=select_files
)
open_button2.pack(expand=True)
open_button2.place(x=350, y=25)

canvas2 = Canvas(gui, width = 300, height = 300)      
canvas2.pack()      
canvas2.place(x=350, y=75)
img2 = ImageTk.PhotoImage(Image.open("02.jpg"))  
canvas2.create_image(0,0, anchor=NW, image=img2)  

#input for threshold
block_label = Label(gui, text='Block size:')
block_label.place(x=25, y=400)

block_input = Entry(gui)
block_input.place(x=90, y=400)

# generate
open_button2 = Button(
    gui,
    text='Generate result',
    command=select_files
)
open_button2.pack(expand=True)
open_button2.place(x=350, y=25)

gui.mainloop()