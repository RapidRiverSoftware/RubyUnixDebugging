def what_type(string)
  case string
  when /^(\d+)$/
    'integer'
  when /^(\d+)\.(\d+)$/
    'float'
  when /^(https?:\/\/)?([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?$/i
    'url'
  else
    'string'
  end
end

DATA.readlines.map { |l| l.chomp }.each do |line|
  puts "#{what_type(line)}: #{line}"
end

__END__
1
1.3
Hello world
http://www.google.com
https://www.example.com/accounts/2747520/#/
