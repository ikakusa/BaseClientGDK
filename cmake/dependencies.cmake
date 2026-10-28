include(FetchContent)

# SafetyHook
FetchContent_Declare(safetyhook GIT_REPOSITORY https://github.com/cursey/safetyhook.git GIT_TAG main GIT_SUBMODULES "")
# LibHat
FetchContent_Declare(libhat GIT_REPOSITORY https://github.com/BasedInc/libhat.git GIT_TAG v0.9.0)
# GLM
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG 1.0.1)
# EnTT
FetchContent_Declare(EnTT GIT_REPOSITORY https://github.com/skypjack/entt.git GIT_TAG fe8d7d78c4823e8a66a050bf86f5c6318cf76ce7) # Minecraft 1.26.44
# Yaml
FetchContent_Declare(yaml-cpp GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git GIT_TAG master)
# DirectX Headers
FetchContent_Declare(DirectXHeaders GIT_REPOSITORY https://github.com/microsoft/DirectX-Headers.git GIT_TAG v1.606.4)

FetchContent_MakeAvailable(
        safetyhook
        libhat
        glm
        EnTT
        yaml-cpp
        DirectXHeaders
)
