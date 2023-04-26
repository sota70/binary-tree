#include <iostream>

#define NULL_PTR_NUM -1

/*
 * 二分探索木を表すクラス
 *
 * member tree: 木のノードを入れるための配列
 * member capacity 木の最大要素数
 * member current_size 現在木(member tree)に入っている要素数
 */
class binary_search_tree {

public:
  /*
   * コンストラクター
   */
  binary_search_tree(int _capacity) : capacity(_capacity) {
    tree = (int *)malloc(sizeof(int) * _capacity);
  }

  /*
   * デストラクター
   */
  ~binary_search_tree() { free(tree); }

  /*
   * 二分探索木に新しいノードを入れる関数
   * 入れる際に、親と左の子と右の子の関係が
   * left_child < parent < right_childとなるような
   * 位置を探して、そこに入れる
   * NOTE: 親の左の子は、親の位置 * 2 + 1で求まる
   *       親の右の子は、親の位置 * 2 + 2で求まる
   *
   * param new_node: 新しいノードの値(n > 0)
   * return: 無し
   */
  void insert(int new_node) {
    int current_node = 0;
    bool found_pos = false;
    if (current_size < 1) {
      _insert(new_node, 0);
      return;
    }
    // 適切な場所が見つかるまで探し続ける
    // TODO: 適切な場所が見つからなかった場合の処理を実装する
    while (!found_pos) {
      if (new_node < tree[current_node]) {
        if (tree[current_node * 2 + 1] == NULL_PTR_NUM) {
          _insert(new_node, current_node * 2 + 1);
          found_pos = true;
          continue;
        }
        current_node = current_node * 2 + 1;
        continue;
      }
      if (tree[current_node * 2 + 2] == NULL_PTR_NUM) {
        _insert(new_node, current_node * 2 + 2);
        found_pos = true;
        continue;
      }
      current_node = current_node * 2 + 2;
    }
  }

  /*
   * 二分探索木のノードが入った配列を返す関数
   * NOTE: binary_search_treeのオブジェクト自体が破壊された時
   *       同時にノードが入った配列も破壊されるので、注意が必要
   *
   * return: 二分探索木のノードが入った配列
   */
  int *get_tree() { return tree; }

private:
  int *tree;
  int capacity;
  int current_size = 0;

  /*
   * 指定した位置に新しいノードを入れる関数
   * NOTE: この時に、新しいノードは左の子と右の子を持っていないことを表すために
   *       左の子と右の子の位置にNULL_PTR_NUM(-1)を入れている
   *       これで、値が-1の場合は子供が居ないことが分かる
   *
   * param new_node: 新しいノードの値(n > 1)
   * param pos: 新しいノードを入れる場所
   */
  void _insert(int new_node, int pos) {
    printf("data: %d, pos: %d\n", new_node, pos);
    tree[pos] = new_node;
    tree[pos * 2 + 1] = NULL_PTR_NUM;
    tree[pos * 2 + 2] = NULL_PTR_NUM;
    current_size++;
  }
};

int main();

int main() {
  binary_search_tree tree(10);
  tree.insert(15);
  tree.insert(9);
  tree.insert(19);
  for (int i = 0; i < 10; i++) {
    printf("%d ", tree.get_tree()[i]);
  }
  printf("\n");
  return 0;
}
