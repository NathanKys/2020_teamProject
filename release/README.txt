Regex 라이브러리 프로젝트에 링크
1. https://sourceforge.net/projects/gnuwin32/files/regex/2.7/regex-2.7-bin.zip/download 링크를 통해 라이브러리 다운
2. 프로젝트 속성 -> C/C++ 추가 포함 디렉터리에 regex-2.7-bin\include를 추가한다.
3. 링커 -> 추가 라이브러리 디렉터리에 regex-2.7-bin\lib를 추가한다.
4. 링커 -> 입력 -> 추가 종속성에 regex.lib만 추가한다. regex-bcc.lib 추가하면 오류 발생.
	regex2.dll 오류가 발생하면 regex-2.7-bin\bin에 있는 regex2.dll을 직접 프로젝트 폴더 내로 옮겨주세요
	
콘솔 인코딩은 utf-8로 설정해서 열어주시면 감사하겠습니다.