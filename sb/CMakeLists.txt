if (TARGET tinyusb_device)
    add_executable(sb
            main.c
            )

    # pull in common dependencies
    target_link_libraries(sb pico_stdlib hardware_adc pico_multicore hardware_flash hardware_sync)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(sb 1)
    pico_enable_stdio_uart(sb 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(sb)

elseif(PICO_ON_DEVICE)
    message(WARNING "not building sb because TinyUSB submodule is not initialized in the SDK")
endif()
