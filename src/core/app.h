#ifndef APP_H
#define APP_H

// Class for all applications
class App {
	public:
    const char *title;
	  virtual void onStart()  = 0;
	  virtual void onExit()   = 0;
	  virtual void update()   = 0;
	  virtual void draw()     = 0;
	  virtual ~App() {};
};


#endif // APP_H

