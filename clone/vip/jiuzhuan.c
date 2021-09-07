// jiuzhuan.c ��ת��

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY "��ת��" NOR, ({ "jiuzhuan jindan", "dan" }) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ�Ž�ɫ��"ZJURL("cmds:eat jiuzhuan jindan")ZJSIZE(20)"�ɵ�"NOR"����˵��̫���Ͼ�"
			    "�����������鵤��ҩ����������������ԡ�\n");
		set("spectxt", "��������������ԡ�\n");
		set("value", 5000000);
		set("yuanbao", 500);
		set("unit", "��");
            set("no_shop",1);
            set("no_sell",1);
            set("no_give",1);
            set("no_drop",1);
            set("no_get",1);
            //set("no_put",1);
		set("only_do_effect", 1);
		set("suit_point",300);
	}
}

int do_effect(object me)
{
	int effect;
	 mapping my;

	log_file("static/using", sprintf("%s(%s) eat ��ת�� at %s.\n",
		 me->name(1), me->query("id"), ctime(time())));

	effect = 0;
	message_vision("$Nһ������������һ��" + this_object()->name() +
		       "��\n", me);
	if (me->query("gift/xiandan") < 4 && random(2))
	{
		effect++;
		write(HIM "������Լ���ͷ�Ը������ˡ�"NOR"\n");
		me->add("gift/xiandan", 1);
		me->add("int", 1);
		write("\n "+HIR+"��ϲ�㣺"+NOR+HIG+"���þ�ת�𵤳ɹ������������ԡ������ˣ�����"NOR"\n");
	}

	if (me->query("gift/unknowdan") < 4 && random(2))
	{
		effect++;
		write(HIR "������Լ����ȽŸ�����ˡ�"NOR"\n");
		me->add("gift/unknowdan", 1);
		me->add("dex", 1);
		 write("\n "+HIR+"��ϲ�㣺"+NOR+HIG+"���þ�ת�𵤳ɹ������������������ˣ�����"NOR"\n");
	}

	if (me->query("gift/xisuidan") < 4 && random(2) &&
	    me->query("gender") != "����")
	{
		effect++;
		write(HIC "������Լ�����Ϣ��ͨ���ˡ�"NOR"\n");
		me->add("gift/xisuidan", 1);
		me->add("con", 1);
		 write("\n "+HIR+"��ϲ�㣺"+NOR+HIG+"���þ�ת�𵤳ɹ������������ʡ������ˣ�����"NOR"\n");
	}

	if (me->query("gift/shenliwan") < 4 && random(2))
	{
		effect++;
		write(HIG "������Լ���������ǿ���ˡ�"NOR"\n");
		me->add("gift/shenliwan", 1);
		me->add("str", 1);
		write("\n "+HIR+"��ϲ�㣺"+NOR+HIG+"���þ�ת�𵤳ɹ�������������������ˣ�����"NOR"\n");
	}
	write(HIM "ڤڤ������������ֻ������̨һƬ�����������ޱȡ�"NOR"\n");
	me->add("magic_points", 1000 + random(1000));
	me->add("gift/jiuzhuan", 1);
	my = me->query_entire_dbase();
	my["eff_jing"] = my["max_jing"];
	my["jing"] = my["max_jing"];
	my["eff_qi"] = my["max_qi"];
	my["qi"] = my["max_qi"];
	if (my["jingli"] < my["max_jingli"])
		my["jingli"] = my["max_jingli"];
	if (my["neili"] < my["max_neili"])
		my["neili"] = my["max_neili"];
	 write(HIY "һ�󳩿�֮������û����Ǿ���"NOR"\n");
	destruct(this_object());
	return 1;
}

int query_autoload() { return 1; }