// item: /d/xingxiu/npc/obj/fire.c
// Jay 3/17/96

inherit ITEM;

void create()
{
	set_name("����", ({"fire", "huozhe"}));
	set_weight(80);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "����һ֧��������Ļ��ۣ�����������ȼ(light)������������
���˺ڰ��ĵط�ʹ��(use)��\n");
		set("unit", "֧");
		set("value", 100);
		set("no_light", "����ۣ����˺ڰ��ĵط�ʹ��(use)�Ϳ����ˡ�\n");
	}
	set_temp("count", 10);
}

void init()
{
	add_action("do_light", "dian");
	add_action("do_light", "light");
}

int do_light(string arg)
{
	object me;
	object ob;

	if (! arg)
		return notify_fail("��Ҫ��ʲô������\n");

	me = this_player();

	if (arg=="xisui jing")
		return notify_fail("��������������ϴ�辭�����㲻���ջ١�\n");

	if (! objectp(ob = present(arg, me)) &&
	    ! objectp(ob = present(arg, environment(me))))
		return notify_fail("�����Ϻ͸���û��������������\n");

	notify_fail("�ⶫ������ȥûʲô�õ�ġ�\n");


	if (! ob->fire(me, this_object()))
		return 0;

	if (add_temp("count", -1) < 1)
	{
		write("��ѻ������꣬�����ӵ���һ�ߡ�\n");
		destruct(this_object());
	}

	return 1;
}
