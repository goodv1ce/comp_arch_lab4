cmd_/home/goodvice/study/comp-arch/lab4/test1/hello2.ko := ccache arm-eabi-ld -r -EL -z noexecstack -T ./scripts/module-common.lds -T ./arch/arm/kernel/module.lds  --build-id  -o /home/goodvice/study/comp-arch/lab4/test1/hello2.ko /home/goodvice/study/comp-arch/lab4/test1/hello2.o /home/goodvice/study/comp-arch/lab4/test1/hello2.mod.o ;  true