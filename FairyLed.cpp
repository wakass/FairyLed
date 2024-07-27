#include <stdio.h>
#include "pico/stdlib.h"

#include <PicoLed.hpp>
#include <Effects/Marquee.hpp>
#include <Effects/Stars.hpp>
#include <Effects/Comet.hpp>
#include <Effects/Bounce.hpp>
#include <Effects/Particles.hpp>
#include <Effects/Fairy.hpp>

#define LED_PIN 20
#define LED_LENGTH 95

#define ADVANCE_TIME_DP 100e-3 //50 ms per tick
#define ADVANCE_TICK_MS 25 //one tick every x ms

int main()
{
    stdio_init_all();
    auto ledStrip = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LED_PIN, LED_LENGTH, PicoLed::FORMAT_GRB);
    ledStrip.setBrightness(64);
    ledStrip.setDrawMode(PicoLed::MODE_ADD);
    
    ///Color, speed, length, feedrate
    PicoLed::Comet effectComet(ledStrip, PicoLed::RGB(255,0,255), 25.50, 1.5, 10.5);
    PicoLed::Comet effectComet2(ledStrip, PicoLed::RGB(255,255,255), 7.50, 0.5, 3.5);

    PicoLed::Comet effectCometFary(ledStrip, PicoLed::RGB(255,255,255), 7.50, 0.5, 3.5);
    
    //High faderate to see individual pixels
    PicoLed::Fairy effectFairy(ledStrip, 10.5, ADVANCE_TIME_DP); //Fade rate, advance rate per animation of double pendulum
    effectFairy.addBall(PicoLed::RGB(138, 43,  226), 2.0, 10.0, 50.0); //color, length, speed, chaos (goes to 11?)
    effectFairy.addBall(PicoLed::RGB(0, 100, 50), 2.0, 10.0, 50.0);
    effectFairy.addBall(PicoLed::RGB(0, 100, 0), 2.0, 10.0, 50.0);

    std::vector<PicoLed::Color> rainbowPalette;
    rainbowPalette.push_back( PicoLed::RGB(255, 0, 0) );
    rainbowPalette.push_back( PicoLed::RGB(255, 255, 0) );
    rainbowPalette.push_back( PicoLed::RGB(0, 255, 0) );
    rainbowPalette.push_back( PicoLed::RGB(0, 255, 255) );
    rainbowPalette.push_back( PicoLed::RGB(0, 0, 255) );
    rainbowPalette.push_back( PicoLed::RGB(255, 0, 255) );
    PicoLed::Marquee effectMarquee(ledStrip,rainbowPalette, 7.50, 5.5);
    /// Random lifetime, --> spawn new pixie at location at death..?
    // random speed (7.5-15?), 
    // random direction over time 
    
    uint32_t timeNow = to_ms_since_boot( get_absolute_time() );

    while (true) {
        if (effectFairy.animate())
            ledStrip.show();
        // if (effectComet.animate())
        //     ledStrip.show();
        sleep_ms(ADVANCE_TICK_MS);

        timeNow = to_ms_since_boot( get_absolute_time() );

    }
    return 0;
}
