//
//  SDInput.h
//  Ship Demo
//
//  This input controller is primarily designed for keyboard control.  On mobile
//  you will notice that we use gestures to emulate keyboard commands. They even
//  use the same variables (though we need other variables for internal keyboard
//  emulation).  This simplifies our design quite a bit.
//
//  Author: Walker White
//  Version: 1/10/17
//
#ifndef __SD_INPUT_H__
#define __SD_INPUT_H__
#include <cugl/cugl.h>

/**
 * This class represents player input in the ship demo.
 *
 * This input handler uses the CUGL input API.  It uses the polling API for
 * keyboard, but the callback API for touch.  This demonstrates a mix of ways
 * to handle input, and the reason for hiding it behind an abstraction like
 * this class.
 *
 * Unlike CUGL input devices, this class is not a singleton.  It must be 
 * allocated before use.  However, you will notice that we do not do any
 * input initialization in the constructor.  This allows us to allocate this 
 * controller as a field without using pointers. We simply add the class to the 
 * header file of its owner, and delay initialization (via the method init()) 
 * until later. This is one of the main reasons we like to avoid initialization 
 * in the constructor.
 */
class ShipInput {
private:
    /** Whether or not this input is active */
    bool _active;

    // KEYBOARD EMULATION
    /** Whether the reset key is down */
    bool  _keyReset;
    
    /** Force generated by the left arrow key */
    float _forceLeft;
    /** Force generated by the right arrow key */
    float _forceRight;
    /** Force generated by the up arrow key */
    float _forceUp;
    /** Force generated by the down arrow key */
    float _forceDown;
    /** The thrust produced by the keyboard only */
    cugl::Vec2 _keybdThrust;
    
    // TOUCH SUPPORT
    /** The initial touch location for the current gesture */
    cugl::Vec2 _dtouch;
    /** The timestamp for the beginning of the current gesture */
    cugl::Timestamp _timestamp;

protected:
    // Input results
    /** Whether the reset action was chosen. */
    bool _resetPressed;
    /** The thrust produced by the player input */
    cugl::Vec2 _inputThrust;
    
public:
#pragma mark -
#pragma mark Constructors
    /**
     * Creates a new input controller.
     *
     * This constructor does NOT do any initialzation.  It simply allocates the
     * object. This makes it safe to use this class without a pointer.
     */
    ShipInput(); // Don't initialize.  Allow stack based
    
    /**
     * Disposes of this input controller, releasing all listeners.
     */
    ~ShipInput() { dispose(); }
    
    /**
     * Deactivates this input controller, releasing all listeners.
     *
     * This method will not dispose of the input controller. It can be reused
     * once it is reinitialized.
     */
    void dispose();
    
    /**
     * Initializes the input control
     *
     * This method works like a proper constructor, initializing the input
     * controller, allocating memory and attaching listeners.
     *
     * @return true if the controller was initialized successfully
     */
    bool init();
    
    
#pragma mark -
#pragma mark Input Detection
    /**
     * Returns true if the input handler is currently active
     *
     * @return true if the input handler is currently active
     */
    bool isActive( ) const { return _active; }
    
    /**
     * Processes the currently cached inputs.
     *
     * This method is used to to poll the current input state.  This will poll 
     * the keyboad and accelerometer.
     * 
     * This method also gathers the delta difference in the touches. Depending 
     * on the OS, we may see multiple updates of the same touch in a single 
     * animation frame, so we need to accumulate all of the data together.
     */
    void update(float dt);
    
    /**
     * Clears any buffered inputs so that we may start fresh.
     */
    void clear();

    
#pragma mark -
#pragma mark Input Results
    /**
     * Returns the current input thrust.
     *
     * The thrust is determined by the last input method.
     *
     * @return The input thrust
     */
    const cugl::Vec2& getThrust() { return _inputThrust; }
    
    /**
     * Returns true if the reset button was pressed.
     *
     * @return true if the reset button was pressed.
     */
    bool didReset() const { return _resetPressed; }
    
    
#pragma mark -
#pragma mark Touch Callbacks
    /**
     * Callback for the beginning of a touch event
     *
     * @param t     The touch information
     * @param event The associated event
     */
    void touchBeganCB(const cugl::TouchEvent& event, bool focus);
    
    /**
     * Callback for the end of a touch event
     *
     * @param t     The touch information
     * @param event The associated event
     */
    void touchEndedCB(const cugl::TouchEvent& event, bool focus);
};

#endif /* __SD_INPUT_H__ */
