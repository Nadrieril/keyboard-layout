def do:
    if type == "string" then
        "=" + (
        @uri "\(.)"
            | gsub("%23"; "#")
            | gsub("%26"; "&")
            | gsub("%2B"; "+")
            | gsub("%2C"; ",")
            | gsub("%2F"; "/")
            | gsub("%3A"; ":")
            | gsub("%3B"; ";")
            | gsub("%3D"; "=")
            | gsub("%3F"; "?")
            | gsub("%40"; "@")

            | reduce ("/@;_&=:" | split("") | .[]) as $escape (.; gsub($escape; "/" + $escape))
        )
    elif type == "object" then
        "_" + (to_entries | map("\(.key)\(.value | do)") | join("&")) + ";"
    elif type == "array" then
        "@" + (map(do) | join("&")) + ";"
    else ":\(.)" end
;

do
