# Review HTML

## HTML tag

제일 먼저 `<!DOCTYPE html>` 을 문서 상단에 작성하고, 그 후 문서의 루트인 html 태그를 열면서 마크업 작업을 시작하게 된다.

### head에 사용되는 태그

문서에 대한 설명이 나와 있는 부분이다.

#### `<title>`

사이트의 이름을 나타내는 태그로 브라우저 탭에 나와 있는 것이 title 태그의 text node이다.

#### `<meta>`

메타데이터를 담는 태그로 보통 해당 html 파일이 UTF-8 인코딩 방식을 사용한다고 브라우저에 알릴 때 사용하고 그 외 사이트의 설명, 키워드, 저자 등 SEO을 위해서도 사용한다.

### body에 사용되는 태그

문서에 대한 내용이 나와 있는 부분이다.

#### `<div>`

"순수" 컨테이너로서 아무것도 표현하지 않기 때문에 class, id를 지정해서 스타일을 입혀 많이 쓰는 주요한 태그

#### `<p>`

paragraph를 뜻하며 말 그대로 단락을 표현할 때 사용한다. 생활코딩에서는 br도 줄 바꿈으로 사용한다고 했는데 Medium과 같은 대형 블로그 플랫폼에서도 일괄적으로 p 태그만 사용한다.

#### `<ul>` & `<li>`

li는 list를 나열할 때 사용하고 ul는 li의 parent element로 다른 list와 구분하기 위해 사용한다.

#### `<table>`

tabular data를 위해 사용한다.

예전에 해당 태그로 layout을 짜는 경우가 있었는데 성능상의 문제는 없지만 MDN Docs에 따르면 3가지 문제가 생긴다고 한다.

- 시각 장애 사용자들의 접근성을 저해
  - 마크업이 더 복잡해져서 screen readers의 결과가 혼란스럽게 나올 수가 있다.
- tag soup을 일으킴
  - tag soup: 문법적으로 잘못된 구조를 짠 행위
- responsive 하지 않음
  - 기본적으로 내용에 따라 크기가 달라지기 때문에 다양한 장치에서 정상적으로 보이게 추가 작업이 필요함
  
#### `<form>`

정보를 모으고 HTTP request를 만드는 역할이고 action 속성에 요청할 주소, method 속성에 GET, POST와 같은 HTTP method를 담는다.

#### `<input>`

입력받는 태그로 다양한 type의 입력을 받을 수 있다. label 태그의 for 속성 과 input의 name 속성이 같게 함으로써 label을 클릭하여 해당 input이 focus 되게 할 수 있다. text, pwd, num, range, ckbox, radio와 같은 type이 존재한다.

codecademy에서는 속성값을 통해 validation을 수행했지만 보통 더 다양한 조건을 위해 regex를 사용해서 validation을 수행한다.

#### `<select>` & `<datalist>`

둘다 option 태그로 드롭다운을 만들 수 있지만 select는 특정한 option만 선택할 수 있고 datalist는 input과 같이 사용자가 원하는 값도 입력할 수 있고 select 처럼 특정한 option을 선택할 수 있다. 자동완성과 같은 기능을 지원하는 것이다.

## Semantic HTML

각 태그의 의미에 맞게 HTML 문서를 마크업 하는 것으로 예를 들어 h1 태그는 이 페이지에서 최상위 제목을 의미하므로 해당 의미에 맞게 마크업을 해야 한다. h1을 사용하지 않고 p 또는 span 태그에 스타일을 입혀 사용할 경우 Non-Semantic인 것이다.

Semantic하게 마크업을 함으로써 접근성, SEO 에 더 좋은 영향을 끼치며 개발자가 HTML 파일을 보고 더 잘 이해할 수 있도록 도와주기도 한다.

### Semantic Elements

form, table, article 등을 Semantic Elements라 하며 div, span의 경우엔 Non-semantic Elements라 한다.

- section
  - A section, in this context, is a thematic grouping of content, typically with a heading
  - heading을 가진 content를 주제별로 그룹화하는 element
  - 챕터, 소개, 뉴스 기사들, 연락 정보 등에 사용
- article
  - The article element represents a self-contained composition in a document, page, application, or site and that is, in principle, independently distributable or reusable.
  - page 내에서 단독적인 내용이 있어 분리가 필요할 때 사용
  - 포럼 글, 블로그 글, 댓글, 상품 카드, 뉴스 기사 등에 사용
- header
  - The header element represents a group of introductory or navigational aids.
  - 그룹의 소개와 nav를 위해서 존재
  - heading elements, logo, 저자 소개 등을 보통 포함
- footer
  - The footer element represents a footer.
  - 저자, 관련된 문서, 저작권 등을 포함
- nav
  - The nav element defines a set of navigation links.
  - 모든 nav 요소가 포함되지 않고 major nav block만 포함
- aside
  - The aside element defines some content aside from the content it is placed in.
  - 콘텐츠의 부가 설명등을 할때 사용.
- figure
  - The figure tag specifies self-contained content, like illustrations, diagrams, photos, code listings, etc.
  - figcaption을 사용하면 사진에 대한 caption도 달을 수 있다.

보통 블로그 플랫폼과 같은 글을 작성하는 사이트에서 위와 같은 Semantic element를 잘 지키면서 사용하는 것 같다.

> ref. [HTML Semantic Elements - W3schools](https://www.w3schools.com/html/html5_semantic_elements.asp), [HTML5 - W3.org](https://www.w3.org/TR/2011/WD-html5-20110405/)

## WHY?

사소한 궁금증으로 찾아본 것들 정리

### 왜 `<!DOCTYPE HTML>`을 문서 상단에 위치 시킬까?

하지 않는다면 Quirks Mode로 인식하여 Navigator 4, Internet Explorer 5와 같은 구형 브라우저가 layout을 emulate 하는 것과 같이 작동하게 된다. 따라서 이러한 상황을 피하고자 반드시 해당 태그를 작성하고 시작해야 한다.

> ref. [Quirks Mode - Mdn web docs](https://developer.mozilla.org/en-US/docs/Web/HTML/Quirks_Mode_and_Standards_Mode)

### input vs button 차이?

둘은 같은 역할을 하는 element이지만 button은 img와 같은 element를 추가할 수 있지만 input은 text node만 추가할 수 있다.

button의 기본 submit으로 다른 기능을 위해 사용할 거면 type="button"을 명시하고 또한 img을 childe node에 추가했다면 반드시 img가 보이지 않을 때 보일 텍스트를 alt 속성에 채워두자.

> ref. [17.5 The BUTTON element - W3.org](https://www.w3.org/TR/html4/interact/forms.html#h-17.5)

### article vs section

article은 문서 내 독립적인 내용을 나눌 때 사용하고 section은 문서를 나눌 때 사용한다. 즉 article은 서로 관련 없는 글들을 나눌 때 사용하고 section은 그렇지 않을 때 사용하면 된다.

Medium 블로그 플랫폼을 보면 헤더, 본문을 article로 감싸고 article 안에 있는 본문은 section으로 감싸서 사용한다. 다만 이와같이 article > section 순서로만 중첩해서 사용해야 하는 건 아니다(반대로 중첩이 되어도 상관이 없다).

### section vs div

container로써 스타일링 목적 또는 scripting 목적일 때에는 div의 사용을 권장한다. section은 명시적으로 문서의 윤곽을 나타내기 위해 사용하는 것이 적절하다.

> ref. [4.4.2 section - W3.org](https://www.w3.org/TR/2011/WD-html5-20110405/sections.html#the-section-element/), [4.4.4 article - W3.org](https://www.w3.org/TR/2011/WD-html5-20110405/sections.html#the-article-element)
