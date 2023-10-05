# 3 students are suspected of doing illegal things with computers of the university.
# They know that the computers send logs to the server and so hid their activity from the server.
# But they don't know that logs are also saved on the different computers.
# There are the logs from the server and from the students, use diff(1) to compare them and find which students are innocent.

diff -sq logs/syslog.log logs/student1.log
diff -sq logs/syslog.log logs/student2.log
diff -sq logs/syslog.log logs/student3.log