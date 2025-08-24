
create_clock -period 10.000 -name clk_100 -waveform {0.000 5.000} [get_ports clk_100MHz]
set_property CFGBVS        VCCO          [current_design]
set_property CONFIG_VOLTAGE 3.3          [current_design]
set_property IOSTANDARD LVCMOS33 [get_ports clk_100MHz]
set_property PACKAGE_PIN N15 [get_ports clk_100MHz]  

#create_clock -name clk_25 -period 40.000 [get_nets clk_25MHz]

set_property IOSTANDARD LVCMOS33 [get_ports pwm_out]
set_property PACKAGE_PIN B13 [get_ports pwm_out]  
set_property DRIVE 8 [get_ports pwm_out]
set_property SLEW SLOW [get_ports pwm_out];  

set_property IOSTANDARD LVCMOS33 [get_ports pwm_outr]
set_property PACKAGE_PIN B14 [get_ports pwm_outr]  
set_property DRIVE 8 [get_ports pwm_outr]
set_property SLEW SLOW [get_ports pwm_outr]; 


set_property IOSTANDARD LVCMOS33 [get_ports audioen]
set_property PACKAGE_PIN C14 [get_ports audioen] 

set_property -dict { PACKAGE_PIN V17   IOSTANDARD TMDS_33 } [get_ports {hdmi_tmds_clk_n}]
set_property -dict { PACKAGE_PIN U16   IOSTANDARD TMDS_33 } [get_ports {hdmi_tmds_clk_p}]

set_property -dict { PACKAGE_PIN U18   IOSTANDARD TMDS_33  } [get_ports {hdmi_tmds_data_n[0]}]
set_property -dict { PACKAGE_PIN R17   IOSTANDARD TMDS_33  } [get_ports {hdmi_tmds_data_n[1]}]
set_property -dict { PACKAGE_PIN T14   IOSTANDARD TMDS_33  } [get_ports {hdmi_tmds_data_n[2]}]
                                    
set_property -dict { PACKAGE_PIN U17   IOSTANDARD TMDS_33  } [get_ports {hdmi_tmds_data_p[0]}]
set_property -dict { PACKAGE_PIN R16   IOSTANDARD TMDS_33  } [get_ports {hdmi_tmds_data_p[1]}]
set_property -dict { PACKAGE_PIN R14   IOSTANDARD TMDS_33  } [get_ports {hdmi_tmds_data_p[2]}]

set_property IOSTANDARD LVCMOS25 [get_ports {sw[1]}]
set_property PACKAGE_PIN F2 [get_ports {sw[1]}]    

set_property IOSTANDARD LVCMOS25 [get_ports {sw[0]}]
set_property PACKAGE_PIN G1 [get_ports {sw[0]}]    

set_property IOSTANDARD LVCMOS25 [get_ports {sw[2]}]
set_property PACKAGE_PIN F1 [get_ports {sw[2]}] 

set_property IOSTANDARD LVCMOS25 [get_ports {sw[3]}]
set_property PACKAGE_PIN E2 [get_ports {sw[3]}] 

set_property IOSTANDARD LVCMOS25 [get_ports voldown_button]
set_property PACKAGE_PIN J2 [get_ports voldown_button]  

set_property IOSTANDARD LVCMOS25 [get_ports volup_button]
set_property PACKAGE_PIN J1 [get_ports volup_button]

set_property IOSTANDARD LVCMOS25 [get_ports rewind_button]
set_property PACKAGE_PIN G2 [get_ports rewind_button]

set_property IOSTANDARD LVCMOS25 [get_ports skip_button]
set_property PACKAGE_PIN H2 [get_ports skip_button]  