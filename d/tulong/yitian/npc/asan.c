#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("����", ({ "a san", "a", "san" }));
	set("long", "һ����ʮ��������ӣ�������¶������Ǵ�\n"
		    "����һ�����룬˫�ۼ����ʵ�ޱȣ�һ����\n"
		    "֪����Һ��֡�\n");
	set("title", HIR "���������ɸ���" NOR);
	set("gender", "����");
	set("age", 55);
	set("attitude", "peaceful");
	set("shen_type", -1);

	set("per", 30);
	set("str", 60);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("max_qi", 4400);
	set("max_jing", 1400);
	set("neili", 5000);
	set("max_neili", 5000);
	set("jiali", 200);
	set("combat_exp", 1600000);

	set("chat_chance_combat", 200);
	set("chat_msg_combat", ({
		(: perform_action, "finger.fumo" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}) );

	set_skill("literate", 100);
	set_skill("buddhism", 150);
	set_skill("sanscrit", 150);
	set_skill("force", 250);
	set_skill("dodge", 250);
	set_skill("unarmed", 250);
	set_skill("parry", 250);
	set_skill("finger", 250);
	set_skill("shaolin-shenfa", 250);
	set_skill("yijinjing", 250);
	set_skill("jingang-zhi", 250);

	map_skill("dodge", "shaolin-shenfa");
	map_skill("force", "yijinjing");
	map_skill("finger", "jingang-zhi");
	map_skill("parry", "jingang-zhi");

	prepare_skill("finger", "jingang-zhi");

	setup();
	carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
	add_action("begin","bi");
}
int accept_fight(object who)
{
	command("say û�����ķԸ��Ҳ�����֡�");
	return 0;
}

int accept_hit(object who)
{
	command("say û�����ķԸ��Ҳ�����֡�");
	return 0;
}

int accept_kill(object who)
{
	command("say �����̵ģ�����������ǰ��Ȼ�Ҷ���ɱ�ˡ�");
	return notify_fail("ɲ�Ǽ���ֻ���ò���óȻ���֡�\n");
}

int accept_ansuan(object who)
{
	return notify_fail("����밵�㣬����ֻ��¥����Ӱ�ζ����������������\n");
}

int begin()
{
	object weapon;
	object me=this_player();
	object obj=this_object();

	if (objectp(present("he taichong", environment())))
	return 0;
/*
	if (! me->query_temp("win_he"))
	{
		command("heng");
		command("say ������˭��Ϊ�θղŲ���ս���������û�����ˡ�");
		return notify_fail("������������������������\n");
	}
*/
	if (objectp(weapon = me->query_temp("weapon")))
	{
		command("say �Һ���ȿ��֣��뽫" + weapon->name() + "���¡�");
		return notify_fail("������������������������\n");
	}

	command("grin");
	command("say �ã�");
	message_vision(HIY "$NͻȻ���һ����������צ��ʳָ΢������$n" HIY
			   "ֱ�˶��������������������ڵĴ������ָ��"NOR"\n",
			   obj,this_player());

	me->set_temp("bi",1);
	set("anti",me);
	obj->kill_ob(this_player());
	this_player()->kill_ob(obj);
	return 1;
}

void die()
{
	if (objectp(query("anti")))
	{
		message_vision(HIR "\nֻ�����������Һ���ȫ������ؽھ�Ȼ�ѱ�$n" HIR
				   "һһ�������۶ϣ����һ����̱���ڵء�"NOR"\n",
				   this_object(),query("anti"));

		message_vision(CYN "\n���������ڵأ�һ����ʹ��ȫ��Ѫɫ��������˵"
				   "������������С�����ܡ�������δ˵�꣬�����˹�ȥ��"NOR"\n",
				   this_object());

		message_vision(CYN "�������˵��ڵ��ϵİ���һ�ۣ����ޱ����˵����"
				   "�����ˣ�����̧��ȥ����"NOR"\n",
				   this_object());

		message_vision(CYN "����ת��ͷ��$n" CYN
				   "΢Ц����������ѽ�������ð�������ȡ���"NOR"\n",
				   this_object(),query("anti"));

		query("anti")->set_temp("win_asan",1);
		query("anti")->delete_temp("bi");
		query("anti")->delete_temp("win_he");
		destruct(this_object());
	}
::die();
}


