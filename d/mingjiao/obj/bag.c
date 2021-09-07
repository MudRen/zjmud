// bag.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("�Ͳ���", ({ "bag", "bao" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ���Ͳ�������\n");
		set("value", 500);
		set("material", "cloth");
	}
	set("book_count", 0);
}

void init()
{
	if (this_player() == environment())
	{
		add_action("do_open", "open");
		add_action("do_open", "unpack");
		add_action("do_open", "dakai");
	}
}

int do_open(string arg)
{
	object me, book;
	object where;

	if (! arg || ! id(arg))
		return 0;

	if (query("book_count") < 1)
	{
		write("�Ͳ�������ʲôҲû���ˡ�\n");
		return 1;
	}

	me = this_player();
	where = environment(me);
	message_vision("$N����ذ��Ͳ�������ʱ������ԭ����һ��"
		       "�����ľ��飬ֻ���Ͳ����ý��ܣ��䳤�ڲ�"
		       "��Գ��֮�У���ҳ��Ȼ�������\n", me);
	book = new("/clone/book/jiuyang-book");
	book->move(file_name(where));
	add("book_count", -1);
	return 1;
}

