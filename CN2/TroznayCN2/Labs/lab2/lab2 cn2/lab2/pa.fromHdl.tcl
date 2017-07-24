
# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

create_project -name lab2 -dir "C:/Users/student/Desktop/lab2 CN2/lab2/planAhead_run_1" -part xc6slx16csg324-3
set_param project.pinAheadLayout yes
set srcset [get_property srcset [current_run -impl]]
set_property target_constrs_file "led_game.ucf" [current_fileset -constrset]
set hdlfile [add_files [list {rom.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {fsm.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {led_game.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set_property top led_game $srcset
add_files [list {led_game.ucf}] -fileset [get_property constrset [current_run]]
open_rtl_design -part xc6slx16csg324-3
