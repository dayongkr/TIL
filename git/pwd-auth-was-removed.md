# 비밀번호 인증방식 폐지

이제 슬슬 전공 공부를 시작하고자 Repo도 만들고 공부 자료들을 작성하고 push를 하려고 했더니

``` zsh
remote: Support for password authentication was removed on August 13, 2021.
remote: Please see https://docs.github.com/en/get-started/getting-started-with-git/about-remote-repositories#cloning-with-https-URL for information on currently recommended modes of authentication.
```

위와 같이 더 이상 비밀번호 인증방식은 2021/08/13부로 지원하지 않는다는 경고가 떴다.

해당 링크를 통해 더 알아보니깐 보안 측면에서 더 나은 방식을 사용하기 위해 비밀번호로 인증하는 방식은 폐지됐고 대신 password 위치에 `personal access token`을 입력해야 한다.

`personal access token`을 발급받는 방법은 [링크](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token)를 참조하자!

그래도 간단하게나마 설명하자면 Settings > Developer settings > Personal access tokens > Tokens (classic) > Generate new token(classic) > repo 등 필요한 기능들 체크 끝!

추가로 이번에 Fine-grained PAT이 추가 됐는데 말 그대로 세부적으로 쪼개서 PAT을 발급할 수 있는 기능으로 제한된 PAT을 발급하여 조직에 나눠줄 때 유용할 것 같다.
