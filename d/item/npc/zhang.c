// zhang.c ����ʦ

#include <ansi.h>

inherit KNOWER;

int ask_me();

void create()
{
	set_name("����ʦ", ({ "zhang tianshi", "zhang" }));
	set("age", 57);
	set("gender", "����");
	set("long", "����һλ�ɷ���ǣ���ò��Ȼ�ķ�ʦ��\n");
	set("attitude", "peaceful");
	set("str", 28);
	set("int", 35);
	set("con", 38);
	set("dex", 31);

	set("max_qi", 8000);
	set("max_jing", 8000);
	set("max_neili", 8000);

	set_skill("magic", 200);
	set_skill("taoism", 350);

	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		"����ʦҡҡ���������������飬�����㣬̫���Ͼ��������飿\n",
		"����ʦ�����Ĵ��˼�������\n",
	}));

	set("inquiry", ([
		"����" : (: ask_me :),
		"ûǮ" : "ûǮ��ȥ׬������˵ʲô��",
		"����" : "��Ҫ�ǲ����ҿ��԰��㿴��(show)������Ҫ��ʲô��Ʒ��",
	]));

	setup();
	carry_object("/clone/cloth/dao-cloth")->wear();
}

void init()
{
	add_action("do_show", "show");
	add_action("do_summon", "summon");
}

int ask_me()
{
	command("heihei");
	command("say ��ֻ������������⣬Ѱ������Ī�ᣡҪ"
		"�㱾�˵ģ��ҿɲ��ܰ��������£�");
	tell_object(this_player(), GRN "����ʦ�����������˵��"
		    "���Ҫ������ó������ҿ���(show)��"NOR"\n");
	return 1;
}

int do_summon(string arg)
{
	if (! wizardp(this_player()))
	{
		command("say ��������ǰϹץ��ʲô���������ȥ��");
		return 1;
	}

	return 0;
}

int do_show(string arg)
{
	object money;
	object ob;
	object me;
	int n;

	if (! arg)
		return notify_fail("��Ҫ����ʲô������\n");

	me = this_player();
	if (! objectp(ob = present(arg, me)))
		return notify_fail("������û�����ֶ�����\n");

	if (ob->query("equipped"))
		return notify_fail("���Ƚ��" + ob->name() + "��װ����˵��\n");

	message_vision("$n�ó�һ" + ob->query("unit") + ob->name() +
		       "��$N˵�������а���...��\n",
		       this_object(), me);

	if (ob->query("money_id"))
	{
		command("say ������Ǯ��ʲô�����׸�����Ǿ͸��Һ��ˡ�");
		return 1;
	}

	if (! me->query_temp("paid/����ʦ", 1))
	{
		command("heihei");
		command("say ��...��ôҲ���е���˼��˼�ɣ���"
			"˵ʮ���ƽ���ô������Ȼ��Щ��Ҳ�����ԡ�");
		return 1;
	}

	if (stringp(ob->query("magic/imbue_ob")))
	{
		command("say ��...�ҿ�����Ӧ����" +
			ob->query("magic/imbue_name") +
			CYN "���������ܽ�һ����������Ǳ����" NOR);
		me->delete_temp("paid/����ʦ");
		return 1;
	}

	if (mapp(ob->query("magic/imbue_ok")))
	{
		command("say Ŷ���ҿ��������Ѿ�����Ҫ�ڽ����ˣ�"
			"Ҫ����Ǳ�����ñ�ķ����ˡ�\n");
		return 1;
	}

	if (! ob->is_item_make())
	{
		command("heng");
		command("say ��...��...�ҿ��������˰ɣ�");
		return 1;
	}

	if (ob->item_owner() != me->query("id"))
	{
		command("kick " + me->query("id"));
		command("say ����Ϊ��ɽ�˵����������µİ��������������ģ�");
		return 1;
	}

	if (me->query("can_summon/" + ob->query("id")))
	{
		if (ob->weapon_level() > 1)
		{
			command("poor " + me->query("id"));
			command("say �����ڻ����������ʱ��..."
				"��Ҫ��ʥ�������а���");
		} 
		else
		{
			command("kok " + me->query("id"));
			command("say ������Ѿ���Ե�ˣ���˵���"
				"������ô��ô�");
		}
		return 1;
	}

	message("vision", sort_string(HIM + name() + "�ӿڴ�������һ�Ż�ɫ�ķ�ֽ������������ľ�������Ƿ�ֽ��ȼ�ˣ�ɨ��" + ob->name() + HIM "��Ȼ������ľ�����ˣ������㵸�����������дʣ���̫���Ͼ��������ɴ����
˵��һ�����н����ȵ�����������"NOR"\n", 64), environment());
	message_vision("��⻮��һ���⻪��$N���˷�����Ҳ��֪��������ô���¡�\n",me);
	command("say ���ˣ����ˣ���������ˡ�");
	me->delete_temp("paid/����ʦ");
	me->set("can_summon/" + ob->query("id"), base_name(ob));
	log_file("static/item", sprintf("%s %s sancitfy %s(%s)\n",
			log_time(), log_id(me),
			filter_color(ob->name(1)), ob->query("id")));
	return 1;
}

int accept_object(object who, object ob)
{
	if (! ob->query("money_id"))
	{
		command("say �������ҿ�ûɶ��Ȥ��");
		return 0;
	}

	if (ob->value() < 50000)
	{
		command("say ���Ǹ���������ô�����Ҿ������ˣ�");
		return 1;
	}

	if (ob->value() < 100000)
	{
		command("say ��������Ҳ���е����⣬�Ҿ����㿪һ�ι�ɣ�");
		who->set_temp("paid/����ʦ", 1);
		destruct(ob);
		return 1;
	}

	command("say ��...��...��ô�չ˱��ۣ����ܰ����ʲô��");
	who->set_temp("paid/����ʦ", 1);
	destruct(ob);
	return 1;
}

void fight_ob(object ob)
{
	::fight_ob(ob);
	message_vision("$N��Цһ��������������ͷ��ʲô�˶��С���˵������һָ$n��\n",
		       this_object(), ob);
	ob->unconcious();
}

int accept_fight(object who)
{
	command("say û��Ȥ��");
	return 0;
}

int accept_ansuan(object who)
{
	return notify_fail("����밵�㣬������ǰһ��������̫�����\n");
}

void receive_damage(string type, int n)
{
	return;
}

void receive_wound(string type, int n)
{
	return;
}
