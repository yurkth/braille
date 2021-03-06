#pragma once
#include <fstream>
#include <iostream>
#include "Grid.h"

namespace braille {
    class Canvas : public Grid<bool> {
    private:
        /// <summary>
        /// コンソールの幅(文字数)
        /// </summary>
        size_t consoleWidth;

        /// <summary>
        /// コンソールの高さ(文字数)
        /// </summary>
        size_t consoleHeight;

        /// <summary>
        /// 点字のUnicode計算用
        /// </summary>
        uint8_t pixelMap[8] = { 0x01, 0x02, 0x04, 0x40, 0x08, 0x10, 0x20, 0x80 };

        /// <summary>
        /// 実際に出力する文字
        /// </summary>
        Grid<WCHAR> text;

        /// <summary>
        /// 出力する文字の属性(色など)
        /// </summary>
        Grid<WORD> attrs;

    public:
        Canvas() = default;

        /// <summary>
        /// キャンバスの初期化
        /// </summary>
        /// <param name="_consoleWidth">キャンバスの幅(文字数)</param>
        /// <param name="_consoleHeight">キャンバスの高さ(文字数)</param>
        Canvas(size_t _width, size_t _height)
            : Grid<bool>(_width, _height, 0)
            , consoleWidth(_width / 2)
            , consoleHeight(_height / 4)
            , text(Grid<WCHAR>(consoleWidth, consoleHeight, ' '))
            , attrs(Grid<WORD>(consoleWidth, consoleHeight, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)) {
            if (width % 2 != 0 || height % 4 != 0) {
                std::cout << width << ", " << height << std::endl;
                throwError();
            }
        }

        /// <summary>
        /// キャンバスのドットをコンソール用のグリッドにコピーする
        /// </summary>
        void updateText();

        /// <summary>
        /// 文字をコンソール用のグリッドにコピーする
        /// </summary>
        /// <param name="consoleX">x座標</param>
        /// <param name="consoleY">y座標</param>
        /// <param name="c">コピーする文字</param>
        void setText(size_t consoleX, size_t consoleY, WCHAR c);

        /// <summary>
        /// 文字列をコンソール用のグリッドにコピーする
        /// </summary>
        /// <param name="consoleX">x座標</param>
        /// <param name="consoleY">y座標</param>
        /// <param name="s">コピーする文字列</param>
        void setText(size_t consoleX, size_t consoleY, std::string s);

        /// <summary>
        /// コンソール用のグリッドから文字を取得
        /// </summary>
        /// <param name="consoleX">x座標</param>
        /// <param name="consoleY">y座標</param>
        /// <returns>取得した文字</returns>
        WCHAR getText(size_t consoleX, size_t consoleY) const;

        /// <summary>
        /// 文字の属性を設定する
        /// </summary>
        /// <param name="consoleX">x座標</param>
        /// <param name="consoleY">y座標</param>
        /// <param name="attr">設定する属性</param>
        void setAttr(size_t consoleX, size_t consoleY, WORD attr);

        /// <summary>
        /// 属性用のグリッドから属性を取得
        /// </summary>
        /// <param name="consoleX">x座標</param>
        /// <param name="consoleY">y座標</param>
        /// <returns>取得した属性</returns>
        WORD getAttr(size_t consoleX, size_t consoleY) const;

        /// <summary>
        /// 別のキャンバスを自分に描画する
        /// </summary>
        /// <param name="x">描画の基準にするx座標</param>
        /// <param name="y">描画の基準にするy座標</param>
        /// <param name="sprite">描画するキャンバス</param>
        void draw(size_t x, size_t y, Canvas& spr);

        /// <summary>
        /// 文字列からキャンバスを読み込む
        /// </summary>
        /// <param name="str">0と1からなる文字列(長さはキャンバスのサイズと同じ)</param>
        void load(std::string str);

        /// <summary>
        /// ファイルからキャンバスを読み込む
        /// </summary>
        /// <param name="filename">ファイル名(ファイル内の0と1だけが読み込まれる)</param>
        void loadFromFile(std::string filename);

        /// <summary>
        /// 画面をクリアする
        /// </summary>
        void clear();

        /// <summary>
        /// 領域を指定して画面をクリアする
        /// </summary>
        /// <param name="x">クリアする基準となるx座標</param>
        /// <param name="y">クリアする基準となるy座標</param>
        /// <param name="w">クリアする幅</param>
        /// <param name="h">クリアする高さ</param>
        void clear(size_t x, size_t y, size_t w, size_t h, size_t margin = 0);

        /// <summary>
        /// キャンバスに長方形を描画する
        /// </summary>
        /// <param name="x">基準となるx座標</param>
        /// <param name="y">基準となるy座標</param>
        /// <param name="w">長方形の幅</param>
        /// <param name="h">長方形の高さ</param>
        /// <param name="attr">文字の属性</param>
        /// <param name="margin">外枠の余白</param>
        void rect(size_t x, size_t y, size_t w, size_t h, WORD attr, size_t margin = 0);
    };
}