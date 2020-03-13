# Point-of-Interest-Finder
A command line tool that downloads the pictures of your favourite restaurant, bar, eatery, etc. This tool takes advantage of the Google Places API. <a href="https://developers.google.com/places/web-service/search">HERE</a>. The jq-linux64 binary is necessary for parsing data.

Use it this way:

Type ./a.out "Bramalea city centre"

You get a picutre of Bramalea city centre stored in your current directory. 

Make sure the jq-linux binary is in the same folder as the current directory in which the a.out binary exists. To compile, make sure your development environment has curl.

Compile with g++ c.cpp -lcurl

Troubleshooting: 

chmod +x ./a.out
chmod +x jq-linux64
