# PI

一番円周率に近い式を、改良された？モンテカルロ法で求めていくプログラム。

本当は遺伝的アルゴリズムを使いたかったが、あまりにも早期収束してしまうため失敗した。

#####若干のアルゴリズムの説明

1. 種となる遺伝子（遺伝的アルゴリズムの名残）を20個（適当に決めた）用意する。
2. それぞれの遺伝子に、ユーザーが指定した分の点を用意して、それぞれの点の座標にに乱数を代入。
3. 遺伝子ごとに円の中に入った点の数を元にして円周率の計算をする。
4. M_PIからどのくらい離れているかを基準にしてソートし、一番良い遺伝子の円周率を表示。
5. 一番良い遺伝子を残して乱数を振り直す。
6. ３〜５までを同じ円周率の値が5回（適当に決めた）繰り返すまで続ける。

##使い方

C言語の標準ライブラリ関数しか使っていないので、cloneして、ソースコードをgccでコンパイルした後、実行してください。

	git clone https://github.com/naokisz/PI.git

	gcc -o PI PI.c -lm

	./PI

##ライセンス

GPL ver2.0
