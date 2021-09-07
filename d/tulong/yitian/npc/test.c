#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
	object ling1;
	set_name("����ʹ", ({ "liuyun shi", "liuyun", "shi" }));
	set("long", "һ����ʮ������������ӣ�װ�����죬����\n"
		    "��ͨ��������ʿ������ǲ�˹�����ܽ̽���\n"
		    "��������������ʮ�ĵ�����ʹ��\n");
	set("title", HIB "��˹�ܽ̽�������" NOR);
	set("nickname", HIY "�Ʒ�����ʹ" NOR);
	set("gender", "����");
	set("age", 47);
	set("attitude", "friendly");
	set("shen_type", 1);

	set("per", 23);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("max_qi", 4000);
	set("max_jing", 1800);
	set("neili", 5000);
	set("max_neili", 5000);
	set("jiali", 200);
	set("combat_exp", 1200000);

	set("chat_chance_combat", 200);
	set("chat_msg_combat", ({
		(: perform_action, "sword.xiyan" :),
		(: perform_action, "sword.guanghua" :),
		(: perform_action, "sword.lianxin" :),
		(: perform_action, "sword.canxue" :),
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
	}) );

	set_skill("literate", 100);
	set_skill("sanscrit", 300);
	set_skill("force", 230);
	set_skill("dodge", 230);
	set_skill("unarmed", 230);
	set_skill("parry", 230);
	set_skill("finger", 230);
	set_skill("strike", 230);
	set_skill("sword", 230);
	set_skill("shenghuo-ling", 250);
	set_skill("tougu-zhen", 250);
	set_skill("yinfeng-dao", 250);
	set_skill("shenghuo-xinfa", 250);
	set_skill("qiankun-danuoyi", 250);
	set_skill("sanscrit", 200);

	map_skill("dodge", "qiankun-danuoyi");
	map_skill("force", "shenghuo-xinfa");
	map_skill("finger", "tougu-zhen");
	map_skill("strike", "yinfeng-dao");
	map_skill("parry", "qiankun-danuoyi");
	map_skill("sword", "shenghuo-ling");

	prepare_skill("strike", "yinfeng-dao");
	prepare_skill("finger", "tougu-zhen");

	create_family("��˹�����ܶ�", 32, "����");

	setup();

	if (clonep())
	{
		ling1 = find_object("/clone/book/ling1");
		if (! ling1) ling1 = load_object("/clone/book/ling1");
		if (! environment(ling1))
			ling1->move(this_object());
			ling1->wield();
	}

	carry_object(__DIR__"obj/jiaofu")->wear();
}

void init()
{
	object me;

	me = this_player();

	if (! interactive(me))
		return;

	if (living(this_object()) && present("yitian sword", me))
	{
		command("say �ף����콣��ô������������������ԭ֮��û�����ˣ�");
		kill_ob(me);
		return;
	}

	if (living(this_object()) && present("tulong blade", me))
	{
		command("say �ߣ����������������������Ѿ��غ��ʱ�ˣ�");
		kill_ob(me);
		return;
	}

	if (living(this_object()) && present("shenghuo ling", me))
	{
		command("say �ף�����ô�������ҽ̵�ʥ����컹���ң�");
		return;
	}
}

int recognize_apprentice(object me, string skill)
{
	if (me->query("shen") > 1000)
	{
		command("say ߴ������������³³�������˿���ȥ�����Ǻ��ˣ�������");
		return -1;
	}

	if (skill != "sanscrit")
	{
		command("say ���������ӡ��ѧ��һ�㶫�����㻹��֪�㰡��");
		return -1;
	}
	return 1;
}

int accept_object(object who, object ob)
{
	if (ob->query("id") == "shenghuo ling")
	{
		destruct(ob);
		if (! who->query("can_perform/shenghuo-ling/canxue"))
		{
			if (! who->query_skill("shenghuo-ling", 1))
			{
				command("say ��л����л��");
				command("say �����㲢û���������ϵĶ�����Ҫ���ҵ��ǿ�"
					"�Դ��ڵ㶫�����㡣");
				return 1;
			} else
			if (who->query("character") != "���ռ�թ" &&
			    who->query("character") != "������")
			{
				command("say ��л����л��");
				command("say ��������������Բ��ʣ�Ҫ���ҵ��ǿ��԰���"
					"��ľ��д������㡣");
				return 1;
			} else
			if (who->query("int") < 32)
			{
				command("say ��л����л��");
				command("say ����Ҫ�����������̫�ͣ������ˣ��ҵ���"
					"���԰�����ľ��д������㡣");
				return 1;
			} else
			if (who->query_skill("shenghuo-ling", 1) < 250)
			{
				command("say ��л����л��");
				command("say �����㲢û���������ϵ��书��Ҫ���ҵ��ǿ�"
					"�԰�����ľ��д������㡣");
				return 1;
			} else
			if (who->query_skill("force") < 350)
			{
				command("say ��л����л��");
				command("say ����Ҫ��������ڹ������ô�㣬�ҵ��ǿ�"
					"�԰�����ľ��д������㡣");
				return 1;
			} else
			if (who->query("max_neili") < 5000)
			{
				command("say ��л����л��");
				command("say ������ϧ���������Ϊ���ޣ���Ȼ�ҵ��ǿ���"
					"������ľ��д������㡣");
				return 1;
			} else
			{
				command("say ��л����л��");
				command("say �����书��ǿ����������������о�������"
					"������Ե��");
				command("say �������²����������⵹�ǿ��Խ��������"
					"�ľ��С�");
				message_vision(HIC "$N" HIC "��$n" HIC "�е���ߣ���"
					"���������ֹ��˼��䣬$n" HIC "������ĵ�һЦ"
					"������������ʲô��"NOR"\n", this_object(),
					who);
				who->set("can_perform/shenghuo-ling/canxue", 1);
				tell_object(who, HIC "��ѧ����ʥ���֮��" NOR + HIR
					    "��Ѫ��" NOR + HIC "����"NOR"\n");
				if (who->can_improve_skill("sword"))
					who->improve_skill("sword", 160000);
				if (who->can_improve_skill("shenghuo-ling"))
					who->improve_skill("shenghuo-ling", 160000);
				return 1;
			}
		}
		message_vision(CYN "$N" CYN "������ϲ�Ķ�$n" CYN "�����ٴζ�л����"
			       "�̵�ʥ�ﻹ�ҡ�"NOR"\n", this_object(), who);
		return 1;
	}
	return 0;
}

