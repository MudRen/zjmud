// paper.c
//
// ֽ�ſ������������������Ժ������Ϊautoload��Ʒ���롣
// ����ı�Ҫ��Ϣ��
// draw/type    ͼ��������
// draw/content ͼ��������
// draw/info    ͼ���ĸ�����Ϣ

#include <ansi.h>
#include <command.h>

inherit ITEM;

void create()
{
	set_name("ֽ��", ({"paper", "paper of drawing"}));
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ������ͨͨ�İ�ֽ������ʲôҲû�С�"
			    "�����Ը����Ի�(draw)�㶫�������档\n");
		set("material", "paper");
	}
}

void init()
{
	add_action("do_draw", "draw");
	add_action("do_clear", "clear");
}

int do_draw(string arg)
{
	object me;
	object ob;
	int lvl;

	if (! arg)
		return notify_fail("���뻭ʲô�����Ҫ������ķ羰��"
				   "���� draw here��\n");

	me = this_player();
	lvl = me->query_skill("drawing", 1);
	if (arg != "here" && ! objectp(ob = present(arg, environment(me))))
		return notify_fail("����û������Ҫ���Ķ�����\n");

	if (query("draw"))
		return notify_fail("����ֽ�Ѿ����˶�����������ٻ���Ҫ"
				   "��Ĩȥ(clear)��\n");

	message("vision", me->name() + "�ó�һ֧�ʣ���ֽ�ϲ�֪"
		"������Щʲô��\n", environment(me), ({ me }));

	if (arg == "here")
	{
		tell_object(me, "���ó�һ֧�ʣ���ϸ����ġ����ķ羰��\n");
		if (lvl < 30)
		{
			tell_object(me, "������Ļ�������ʵ����̫���ˣ�"
					"�޴���ʣ�ֻ�ú���ͿĨһ��\n");
			set("draw/content", "�������߰���Ŀ�����������"
					    "ʲô��\n");
			set("draw/info", "unknow");
		} else
		if (lvl < 80)
		{
			tell_object(me, "��Ȼ��Ļ������ɲ���ô��������"
					"����ѧ��һ�㣬��ǿ���á�\n");
			set("draw/content", "���滭����Ȼ��Щ���ң�����"
			    "���ܿ��ó���" + environment(me)->short() +
			    "�ķ羰��\n");
			set("draw/info", base_name(environment(me)));
		} else
		{
			tell_object(me, "������������羰��ʱƮȻԾ��ֽ"
					"�ϡ�\n");
			set("draw/content", "���滭����" + environment(me)->short() +
			    "�ķ羰����Ϊ�����������١�\n");
			set("draw/info", base_name(environment(me)));
		}		

		set("draw/type", "�羰");
	} else
	if (ob->is_character())
	{
		if (ob != me)
		{
			message("vision", me->name() + "��ס�Ĵ���" + ob->name() +
				"�����²�֪���ڻ�Щʲô������\n",
				me, ob);
			tell_object(me, "���ó�һ֧�ʣ���ϸ����ġ" + ob->name() + "��\n");
		} else
		{
			command("consider");
			tell_object(me, "���ó�һ֧�ʣ���ϸ�İ��ռ����е���������Լ���\n");
		}
		if (lvl < 30)
		{
			tell_object(me, "������Ļ�������ʵ����̫���ˣ�"
					"�޴���ʣ�ֻ�ú���ͿĨһ��\n");
			set("draw/content", "�������߰���Ŀ�����������"
					    "ʲô��\n");
			set("draw/info", "unknow");
		} else
		if (lvl < 80)
		{
			tell_object(me, "��Ȼ��Ļ������ɲ���ô��������"
					"����ѧ��һ�㣬��ǿ���á�\n");
			set("draw/content", "���滭����Ȼ��Щ���ң�����"
			    "���ܿ��ó���" + ob->name() + "���е����ơ�\n");
			set("draw/info", ob->query("id"));
		} else
		{
			string msg;
			string einfo;
			object cloth;
			object helmet;
			object hob;

			tell_object(me, "�����������" + ob->name() +
					"��ʱƮȻԾ��ֽ�ϡ�\n");
			msg = "̯��ֽ����";
			if (userp(ob))
			{
				cloth = ob->query_temp("armor/cloth");

				helmet = ob->query_temp("armor/head");
				if (objectp(helmet))
					einfo = "ͷ��" + helmet->name() + "��";
				else
					einfo = "";

				hob = ob->query_temp("handing");
				if (objectp(hob))
					einfo += "����һ" + hob->query("unit") + hob->name() + "��";

				if (ob->query("gender") == "Ů��")
				{
					if (cloth)
						msg += "ֻ������һ��Ů������" + cloth->name() + "��" + einfo;
					else
						msg += "ֻ������һ��Ů��һ˿���ҡ�δ�Ŵ��ƣ�";
				} else
				{
					if (cloth)
						msg += "ֻ������һ����������" + cloth->name() + "��" + einfo;
					else
						msg += "ֻ������һ������̹��¶�飬�������壬";
				}
				msg += LOOK_CMD->description(ob);
				msg = sort_msg(msg, 60);
			}
			msg += "ԭ�����滭����" + ob->name() +
			    "����Ȼ����֮����������ֽ������\n";
			set("draw/content", msg);
			set("draw/info", ob->query("id"));
		}		

		set("draw/type", "����");
	} else
	{
		tell_object(me, "���ó�һ֧�ʣ���ϸ����ġ" + ob->name() + "��\n");
		if (lvl < 30)
		{
			tell_object(me, "������Ļ�������ʵ����̫���ˣ�"
					"�޴���ʣ�ֻ�ú���ͿĨһ��\n");
			set("draw/content", "�������߰���Ŀ�����������"
					    "ʲô��\n");
			set("draw/info", "unknow");
		} else
		if (lvl < 80)
		{
			tell_object(me, "��Ȼ��Ļ������ɲ���ô��������"
					"����ѧ��һ�㣬��ǿ���á�\n");
			set("draw/content", "���滭����Ȼ��Щ���ң�����"
			    "���ܿ��ó���" + ob->name() + "���е����ơ�\n");
			set("draw/info", ob->query("id"));
		} else
		{
			string msg;
			object cloth;

			tell_object(me, "�����������" + ob->name() +
					"��ʱƮȻԾ��ֽ�ϡ�\n");
			msg = "���滭����" + ob->name() +
			    "������֮����\n";
			set("draw/content", msg);
			set("draw/info", ob->query("id"));
		}		

		set("draw/type", "��Ʒ");
	}

	set("no_sell", 1);
	set("value", 1);

	return 1;
}

int do_clear(string arg)
{
	object me = this_player();

	if (! arg || ! id(arg))
		return notify_fail("��Ҫ���ɾ�ʲô������\n");

	if (! query("draw/type"))
	{
		write ("����ɸɾ�����ʲôҲû�У������ٲ��ˡ�\n");
		return 1;
	}

	message_vision("$N����Ľ�ֽ��Ĩ�ɾ���\n", me);
	delete("draw");
	delete("no_sell");
	delete("value");
	return 1;
}

string long()
{
	return query("draw/type") ? query("draw/content") : query("long");
}

string query_autoload()
{
	mapping draw;

	if (! mapp(draw = query("draw")))
		return 0;

	return draw["type"] + "|" + draw["content"] + "|" + draw["info"];
}

void autoload(string param)
{
	string type;
	string content;
	string info;

	if (sscanf(param, "%s|%s|%s", type, content, info) != 3)
	{
		destruct(this_object());
		return;
	}

	set("no_sell", 1);
	set("value", 1);
	set("draw/type", type);
	set("draw/content", content);
	set("draw/info", info);
}
