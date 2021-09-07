// yuenv.c ԽŮ

#include <ansi.h>

inherit NPC;

int ask_me();

void create()
{
	set_name("ԽŮ", ({ "yue nv", "yuenv" }));
	set("long", @LONG
��һһλ���������Ů�����Ϲ���һ˿�����䲻��Ƶİ�˼��
LONG );
	set("gender", "Ů��");
	set("class", "swordsman");
	set("age", 18);
	set("attitude", "friendly");
	set("per", 29);
	set("str", 19);
	set("int", 35);
	set("con", 32);
	set("dex", 35);
	
	set("max_qi", 5000);
	set("max_jing", 2500);
	set("neili", 5000);
	set("max_neili", 5000);
	set("jiali", 50);
	set("combat_exp", 2500000);

	set_skill("force", 250);
	set_skill("dodge", 270);
	set_skill("parry", 270);
	set_skill("sword", 270);
	set_skill("yunv-xinfa", 250);
	set_skill("yuenv-jian", 270);
	set_skill("feiyan-huixiang", 250);

	map_skill("dodge", "feiyan-huixiang");
	map_skill("force", "yunv-xinfa");
	map_skill("sword", "yuenv-jian");

	set("inquiry", ([
		"����" : (: ask_me :),
		"����" : (: ask_me :),
		"��������" : (: ask_me :),
	]));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: perform_action, "sword.pengxin" :),
	}));

 	setup();
	carry_object("/clone/cloth/cloth")->wear();
	carry_object("/clone/weapon/zhujian")->wield();
}

int recognize_apprentice(object ob, string skill)
{
	if (ob->query_temp("can_learn/yuenv/yuenv-jian") &&
	    skill == "yuenv-jian")
		return 1;

	if (ob->query_temp("can_learn/yuenv/sword") &&
	    skill == "sword")
		return 1;

	if (skill == "yuenv-jian")
	{
		if (ob->query("gender") == "Ů��")
		{
			message_vision("$N��Ȧһ�죬��$n����Ҳ�á�\n",
				       this_object(), ob);
			ob->set_temp("can_learn/yuenv/yuenv-jian", 1);
			return 1;
		}
		message_vision("$NƳ��$nһ�ۣ�û����$n��\n", this_object(), ob);
		return -1;
	}

	if (skill == "sword")
	{
		message_vision("$N���˿�$n�����ͷ��������Ҳû��ʲô��ѧ�ġ�\n",
			       this_object(), ob);
		ob->set_temp("can_learn/yuenv/sword", 1);
		return 1;
	}

	command("say ��ֻ����һ�㽣������ɲ�ҪΪ���ҡ�");
	return -1;
}

int ask_me()
{
	object me;

	me = this_player();
	if (me->query("can_perform/yuenv-jian/pengxin"))
	{
		command("say ���ϲ������Цô��ѧ���˻������ң�");
	} else
	if (me->query("gender") != "Ů��")
	{
		command("say ��������û��ʲô�ö��������Ǳ�˵ʲô���������ˡ�");
	} else
	if (me->query("per") >= 30)
	{
		message_vision("$N����$n�����ĵ�̾��һ�������ƺ�������ʲô��\n",
			       this_object(), me);
	} else
	if (me->query_skill("force") < 120)
	{
		command("say ����ڹ�������ô���̸ʲô���У�Ц���˼��ˡ�");
		return 1;
	} else
	if (me->query_skill("yuenv-jian", 1) < 100)
	{
		command("say �㻹�������ҵĽ�����˵�ɣ���Ҫ�ø���Զ������һ���޳ɡ�");
		return 1;
	} else
	{
		command("nod");
		command("say �ðɣ��Ҿͽ�����һ�С��������ġ����Ժ���������... �������˰ɡ�");
		tell_object(me, "������ԽŮ��ָ�㣬���������������һ������\n");
		me->set("can_perform/yuenv-jian/pengxin", 1);
	}
	return 1;
}

void unconcious()
{
	die();
}

