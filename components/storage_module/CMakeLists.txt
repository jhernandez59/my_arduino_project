idf_component_register(
    SRCS "storage_module.cpp"
    INCLUDE_DIRS "."
    PRIV_REQUIRES arduino nvs_flash
)
