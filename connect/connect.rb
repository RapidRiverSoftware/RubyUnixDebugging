require 'socket'

def die(msg)
  STDERR.puts(message)
  exit 1
end

port     = ARGV.shift || die("Usage: $0 port [hostname]")
hostname = ARGV.shift || '127.0.0.1'

s = TCPSocket.new hostname, port

die "Unable to connect to #{hostname}:#{port}: #{$!}" unless s

while line = s.readline
  puts line
end
