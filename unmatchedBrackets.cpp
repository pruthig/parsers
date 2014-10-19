#include<iostream>
#include<fstream>
#include<stack>
#include <gtk/gtk.h>

using namespace std;


int main(){
cout<<"Hello World\n";
fflush(stdout);
GtkWidget *dialog;
GtkFileChooser *chooser;
GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
gint res;

dialog = gtk_file_chooser_dialog_new ("Save File",
                                      //parent_window,
                                      action,
                                      ("_Cancel"),
                                      GTK_RESPONSE_CANCEL,
                                      ("_Save"),
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);
res = gtk_dialog_run (GTK_DIALOG (dialog));
if (res == GTK_RESPONSE_ACCEPT)
  {
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    filename = gtk_file_chooser_get_filename (chooser);
    //open_file (filename);
    g_free (filename);
  }

gtk_widget_destroy (dialog);

return 0;

}

void parser(){
std::stack<char> st;
ifstream ifs;
char topper;
int count = 1;
ifs.open("controlleedevice.c", std::ifstream::in);
char c = ifs.get();

while(ifs.good())
{
		cout<<c;
		char nxt = ifs.peek();
		/*
		if( c == '/'&&  ( nxt == '/' || nxt == '*') ){   //skip the comment
			while( ( c = ifs.get()) != '\n');
		}
		*/
			
		if(c == '\n')
			++count;

		if(c == '(' || c == '{')
			st.push(c);

		if(c == ')'){
			if(!st.empty()){topper = st.top();}
			if(topper != '(' || st.empty()){
				cout<<"Mismatching found for '()'\n";
				cout<<"Line number is : "<<count<<endl;
				cout<<"Stack size is : "<<st.size()<<endl;
				break;
			}
			st.pop();
			//cout<<"Stack size is zero @line number: "<<count<<" for char : "<<c<<endl;
		}

		if(c == '}'){
			
			cout<<"Stack size is : "<<st.size()<<endl;
			if(!st.empty()){topper = st.top();}
			if(topper != '{' || st.empty()){
				cout<<"Mismatching found for '{}' and stack size is " << st.size()<<" and top is :>>  "<<st.top()<<endl;
				cout<<"Line number is : "<<count<<endl;
				//cout<<"Stack size is zero @line number: "<<count<<" for char : "<<c<<endl;
				break;
			}
			st.pop();
		}
		c = ifs.get();
}

}

