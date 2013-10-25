#!/usr/bin/expect -f
# waldo: an expect script template to check MGW via magoo
# test suit is arranged in "test steps", each test step
# results in PASS or FAIL.

# *** procedures section - not to be modified frequently ***

# look for results filename
if {$argc > 0} {
	set outf [open [lindex $argv 0] a]	;# open results file
	puts $outf [timestamp -format %c]
} else {
	set outf ""
}

# debug output
proc DEBUG {x} {
	puts "--- DEBUG: $x\r\n"
}
# flush expect buffer

proc expect_flush {} {
	global expect_out
	expect {
		-timeout 0
		aasdXXCXCXxQQWR
	}
	expect *
	set expect_out(buffer) ""
}

# send a command 
proc cmd {x} {
	sleep 0.001	;# 1ms pause has shown more stability
	send "$x \r"
}

# find expression
proc find_exp { exp } {
	global tst rsp outf expect_out

	# init to FAIL so logic is effecient
	set rsp FAIL
	#DEBUG "Matching: $exp"
	expect {
		-re $exp	{
			#DEBUG "Matched: $expect_out(0,string)"
			set rsp PASS
		} timeout {
			set rsp FAIL
		}
	}

	if {$outf != ""} {
		puts $outf "\[$tst : $rsp\]\r\n\r\n"
	} else {
		puts "\[$tst : $rsp\]\r\n\r\n"
	}
}


# set initial values for a new test step
proc test_step {x} {
	global tst rsp
	set tst $x		;# save test name
	set rsp PASS	;# default result
}

# *** end of procedures section ***

# start worldtime testing 
expect_flush

test_step "run worldtime with no arguments"
spawn "./worldtime"
find_exp "Localtime"

test_step "run worldtime with known arguments"
spawn ./worldtime Washington
find_exp "Washington"

test_step "run worldtime to test upper to lower conversion"
spawn ./worldtime wasHington
find_exp "wasHington"

test_step "run worldtime to test upper to lower conversion"
spawn ./worldtime washington
find_exp "washington"

test_step "run worldtime for san fran"
spawn ./worldtime SanFrancisco
find_exp "SanFrancisco"

test_step "run worldtime for Denver"
spawn ./worldtime Denver
find_exp "Denver"

test_step "run worldtime for Philadelphia"
spawn ./worldtime Philadelphia
find_exp "Philadelphia"

test_step "run worldtime for Chicago"
spawn ./worldtime Chicago
find_exp "Chicago"

test_step "run worldtime London"
spawn ./worldtime London
find_exp "London"

test_step "run worldtime Paris"
spawn ./worldtime Paris
find_exp "Paris"

test_step "run worldtime Beijing"
spawn ./worldtime Beijing
find_exp "Beijing"

test_step "run worldtime Helsinki"
spawn ./worldtime Helsinki
find_exp "Helsinki"

test_step "run worldtime with unknown arguments"
spawn ./worldtime stuff 
find_exp "ERROR"

