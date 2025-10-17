# ZMK Custom Screen for Nice!View Displays

Custom LVGL-based display widgets for keyboards with nice!view displays. 
Currently the display size is fixed to 68 x 160 pixels of the nice view 
display. 


## Widgets

- Layer indicator - Shows current Miryoku layer (BSE, MED, TAP, BTN, NAV, MSE, SYM, NUM, FKT)
- WPM counter - Real-time typing speed (right screen only)
- Battery status - Percentage and charging indicator (both screens)
- Connection status - USB or Bluetooth with profile number (left screen only)
- Custom logos - Miryoku logo (right) and custom logo (left)
- Custom icons - Charge, USB, and Bluetooth icons


## Customization Options

customization is possible via a config file `/display/display_config.h`. The file allows

- selection of the widgets to show
- vertical positioning of the widgets on the screen
- visibility and positioning can be customized per screen


## Supported Environments

Preview your displays with the SDL & LVGL simulator for local development or 
build the zmk firmware straight ahead with github actions for your board. For 
both options visit my [zmk-config](https://github.com/haerttrich/zmk-config) 
repo for detailed instructions.


## Hardware Requirements

- 1bit colored display
- 68x160 resolution
- zmk config available for controller and the display


## Future Features

- display size independence
- imporved customization options
- documentation of all features


## Credits

This repository is strongly inspired by the two related repositories

- [zmk-nice-oled](https://github.com/mctechnology17/zmk-nice-oled)
- [zmk-oled-adapter](https://github.com/mctechnology17/zmk-oled-adapter)

Additionally i have started out building the custom displays for my 
corne custom keyboard with miryoku layout. The logo is taken from there. 
Credits for the logo creation belongs to Manna Harbour and his 
[Miryoku](https://github.com/manna-harbour/miryoku) Repository.
