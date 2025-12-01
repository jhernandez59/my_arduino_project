idf_component_register(
    SRCS "wifi_manager.cpp"
    INCLUDE_DIRS "."
    PRIV_REQUIRES
        wifi_module
        ap_module
        storage_module
        webserver_module
        arduino
)
