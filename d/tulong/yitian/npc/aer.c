#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("����", ({ "a er", "a", "er" }));
	set("long", "�����˰�����ͬ��ʦ�֣�Ҳ������������һ\n"
		    "��һ�ĸ��֣���������һ�ؽ��������£�\n"
		    "�ǳ�������������ʶ��\n");
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
	
	set("max_qi", 5000);
	set("max_jing", 1400);
	set("neili", 7000);
	set("max_neili", 7000);
	set("jiali", 240);
	set("combat_exp", 1800000);

	set("chat_chance_combat", 20);
	set("chat_msg_combat", ({
		(: perform_action, "strike.feng" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}) );

	set_skill("literate", 100);
	set_skill("buddhism", 150);
	set_skill("sanscrit", 150);
	set_skill("force", 270);
	set_skill("dodge", 270);
	set_skill("unarmed", 270);
	set_skill("parry", 270);
	set_skill("strike", 270);
	set_skill("shaolin-shenfa", 270);
	set_skill("yijinjing", 270);
	set_skill("banruo-zhang", 270);

	map_skill("dodge", "shaolin-shenfa");
	map_skill("force", "yijinjing");
	map_skill("strike", "banruo-zhang");
	map_skill("parry", "banruo-zhang");

	prepare_skill("strike", "banruo-zhang");

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
	command("say û�����ķԸ��Ҳ�����֣�ɱ����Ҳһ����");
	return notify_fail("ɲ�Ǽ���ֻ�����²����֡�\n");
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

	if (objectp(present("a san", environment())))
	return 0;
/*
	if (! me->query_temp("win_asan"))
	{
		command("@@");
		command("say ������˭��Ϊ�θղŲ���ս���������û�����ˡ�");
		return notify_fail("������������������������\n");
	}
*/
	if (objectp(weapon = me->query_temp("weapon")))
	{
		command("shake");
		command("say ��Ҳ����ȿ��֣��������" + weapon->name() + "��˵��");
		return notify_fail("������������������������\n");
	}

	command("nod");
	command("say �ҳ����ˡ�");
	message_vision( HIW "$N˫�ֺ�ʮ������$n" HIW 
			    "΢΢һҾ��˫��ƽ�ƣ��ƾ�����˰���ӿ������"NOR"\n",
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
		message_vision( HIR "\nֻ��һ�����죬����ǰ�ر�$n" HIR 
				    "���У��عǾ��ϣ�������Ѫ���磬����������ߵķ���\n"
				    "һ��ֱ���˳�ȥ�����ڵ��϶�Ҳ����һ�¡�"NOR"\n",
				    this_object(),query("anti"));

		message_vision( CYN "������Ϊ���ȣ��ɻ��ǲ�¶��ɫ��ֻ�����ױ���������˵"
				    "������̧��ȥ����"NOR"\n",
				    this_object());

		message_vision( CYN "������תͷ��$n" CYN 
				    "΢Ц�������ܺã���ʣ�¸�������ʤ���������콣���ȡ�߰ɡ���"NOR"\n",
				    this_object(), query("anti"));

		query("anti")->set_temp("win_aer",1);
		query("anti")->delete_temp("bi");
		query("anti")->delete_temp("win_asan");
		destruct(this_object());
	}
::die();
}

