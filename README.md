mc_rtc new FSM controller template
==

This project is a template for a new FSM controller project wihtin [mc_rtc]

It comes with:
- a CMake project that can build a controller in [mc_rtc], the project can be put within [mc_rtc] source-tree for easier updates
- clang-format files
- automated GitHub Actions builds on three major platforms

Quick start
--

1. Renaming the controller from `MinimumJerkController` to `MinimumJerkController`. In a shell (Git Bash on Windows, replace sed with gsed on macOS):

```bash
sed -i -e's/MinimumJerkController/MinimumJerkController/g' `find . -type f`
git mv src/MinimumJerkController.cpp src/MinimumJerkController.cpp
git mv src/MinimumJerkController.h src/MinimumJerkController.h
git mv src/states/MinimumJerkController_Initial.cpp src/states/MinimumJerkController_Initial.cpp
git mv src/states/MinimumJerkController_Initial.h src/states/MinimumJerkController_Initial.h
git mv etc/MinimumJerkController.in.yaml etc/MinimumJerkController.in.yaml
```

2. You can customize the project name in vcpkg.json as well, note that this must follow [vcpkg manifest rules](https://github.com/microsoft/vcpkg/blob/master/docs/users/manifests.md)

2. Build and install the project

3. Run using your [mc_rtc] interface of choice, and setting `Enabled` to `MinimumJerkController`

[mc_rtc]: https://jrl-umi3218.github.io/mc_rtc/
