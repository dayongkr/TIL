# HTML Remind

## HTML tag

제일 먼저 `<!DOCTYPE html>` 을 문서 상단에 작성해야 하는데 하지 않는다면 Quirks Mode로 인식하여 Navigator 4, Internet Explorer 5와 같은 구형 브라우저이 layout을 emulate하는 것과 같이 작동하게 된다. 따라서 이러한 상황을 피하고자 반드시 해당 태그을 작성하고 시작해야 한다.

> ref. [Quirks Mode - Mdn web docs](https://developer.mozilla.org/en-US/docs/Web/HTML/Quirks_Mode_and_Standards_Mode)

그 후 문서의 루트인 html 태그를 열면서 마크업 작업을 시작하게된다.

### head에 사용되는 태그

문서에 대한 설명이 나와 있는 부분이다.

- title
  - 사이트의 이름을 나타내는 태그
  - 보통 브라우저의 탭에 나타남
- meta
  - 메타데이터를 담는 태그
  - 보통 해당 html 파일이 UTF-8 인코딩 방식을 사용한다고 브라우저에 알릴 때 사용
  - 그 외 사이트의 설명, 키워드, 저자 등 SEO을 위해서도 사용

### body에 사용되는 태그

문서에 대한 내용이 나와 있는 부분이다.

- div
  - "순수" 컨테이너로서 아무것도 표현하지 않음
  - class, id를 지정해서 많이 쓰는 주요한 태그
- p
  - paragraph을 뜻하며 말 그대로 단락을 표현할 때 사용
  - 생활코딩에서는 br도 줄 바꿈으로 사용한다고 했는데 Medium과 같은 대형 블로그 플랫폼에서도 일괄적으로 p 태그만 사용
- ul & li
  - li는 list를 나열할 때 사용
  - ul는 li의 parent element로 다른 list와 구분하기 위해 사용
- table
  - tabular data를 위해 사용하는 테이블 tag
  - 예전에 해당 태그로 layout을 짜는 경우가 있었는데 성능상의 문제는 없지만 MDN Docs에 따르면 3가지 문제가 생긴다고 한다.
    - 시각 장애 사용자들의 접근성을 저해
      - 마크업이 더 복잡해져서 screen readers의 결과가 혼란스럽게 나올 수가 있다.
    - tag soup을 일으킴
      - tag soup: 문법적으로 잘못된 구조를 짠 행위
    - responsive 하지 않음
      - 기본적으로 내용에 따라 크기가 달라지기 때문에 다양한 장치에서 정상적으로 보이게 추가 작업이 필요함
  - 잘 사용하지 않는 태그로 알고 있음
