// zisj.c

inherit ITEM;

void create()
{
	set_name("��ˮ��", ({ "zi shuijing", "zi" }));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "����ȥ��ˮ�����࣬ʵ����ȴ���ǣ��ʴ�����ޱȡ�\n");
		set("value", 1);
		set("material", "stone");
	}
	setup();
}
