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

- Selection of the widgets to show
- Vertical positioning of the widgets on the screen
- Placement of widgets independent of split keyboard side


## Hardware Requirements

- 1bit colored display
- 68x160 resolution
- zmk config available for controller and the display


## Usage

1. fork this repo and adjust the `display/display_config.h` file for your widget selection.
2. include this module into your build with `shield: <BOARD> nice_view_adapter nice_custom` and `module: haerttrich/zmk-nice-custom/main` (if forked use your name handle).
3. build as used specified by other zmk code

_for the `miryoku_zmk` repo use the `Build Inputs` action and specify aboves parameters in the build options besides your other configs._


## Extension

this repo is build to with modularity in mind. A widget consists out of drawing the widget, related events and possibly relaying them, as well as assets that go along with the widget. Since all files follow similar structures, use the included widgets, events, etc as examples. No Modifications to the Makefile, etc should be required.

```
haerttrich/zmk-nice-custom
├── display
│   ├── ...
│   ├── assets/
│   │   └── *.c                         <- 1. add the new widget assets like images here (create with lvgl image converter v8 CF_INDEXED_1BIT)
│   ├── widgets/
│   │   └── widget_*.[ch]               <- 2. add the new widgets draw, init, and update functions
│   ├── events/
│   │   └── event_*.[ch]                <- 3. add the new widgets events to trigger changes here
│   ├── screens/
│   │   ├── ...
│   │   └── screen_layouts.c            <- 4. include new widget into draw_widget switch
│   └── relay/                          
│       ├── widget_relay_service.h     
│       ├── widget_relay_service.c      <- 5. add data transfer logic from left to right side 
│       ├── widget_relay.h              
│       └── widget_relay.c              <- 5. add data transfer logic from left to right side
└── ...
```


## Future Features

- display size independence
- documentation of all features


## Credits

This repository is strongly inspired by the related repositories

- [zmk-nice-oled](https://github.com/mctechnology17/zmk-nice-oled) contains custom widgets and animated widgets.
- [zmk-oled-adapter](https://github.com/mctechnology17/zmk-oled-adapter) contains custom widgets.
- [zmk-split-peripheral-output-relay](https://github.com/badjeff/zmk-split-peripheral-output-relay) contains split keyborad communication via relay.
- [miryoku_zmk](https://github.com/manna-harbour/miryoku_zmk) the keymap i've build the displays for. Creator of the miryoku logo.
