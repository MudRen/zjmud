#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("��̫��", ({ "he taichong", "he", "taichong" }));
	set("long", "һ����ʮ������������ӣ�üͷ������ԭ��\n"
		    "����������ɵ����ţ��˳ơ�������������\n"
		    "��̫�壬����������Χ��������֮�󣬱���\n"
		    "�ü����ã���Ѻ�����\n");
	set("title", "�����ɵ���������");
	set("nickname", WHT "��������" NOR);
	set("gender", "����");
	set("age", 58);
	set("attitude", "peaceful");
	set("shen_type", -1);

	set("per", 30);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("max_qi", 3500);
	set("max_jing", 1200);
	set("neili", 4000);
	set("max_neili", 4000);
	set("jiali", 100);
	set("combat_exp", 1400000);

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.fanyin" :),
		(: exert_function, "recover" :),
	}) );

	set_skill("literate", 100);
	set_skill("tanqin-jifa", 250);
	set_skill("qingxin-pushan", 250);
	set_skill("force", 220);
	set_skill("dodge", 220);
	set_skill("unarmed", 220);
	set_skill("parry", 220);
	set_skill("strike", 220);
	set_skill("sword", 220);
	set_skill("lingxu-bu", 220);
	set_skill("songshan-xinfa", 220);
	set_skill("kunlun-jian", 220);
	set_skill("cuixin-zhang", 220);

	map_skill("dodge", "lingxu-bu");
	map_skill("force", "songshan-xinfa");
	map_skill("strike", "cuixin-zhang");
	map_skill("parry", "kunlun-jian");
	map_skill("sword", "kunlun-jian");
	map_skill("tanqin-jifa", "qingxin-pushan");

	prepare_skill("strike", "cuixin-zhang");

	create_family("������", 3, "����");

	setup();
	carry_object("/clone/cloth/cloth")->wear();
	carry_object("/clone/weapon/zhujian")->wield(); 
}

void init()
{
	add_action("begin","bi");
}

int accept_fight(object who)
{
	command("say �ߣ����Һ�̫���������ڣ�Ҳ�ɲ��������");
	return 0;
}

int accept_hit(object who)
{
	command("say �ߣ����Һ�̫���������ڣ�Ҳ�ɲ��������");
	return 0;
}

int accept_kill(object who)
{
	command("heng");
	command("say �Һ�̫�屻�����ù����ס�����û���Ҫ������Ҫɱ�Ͷ��ְɡ�");
	return notify_fail("ɲ�Ǽ���ֻ���²����֡�\n");
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

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
	{
		command("say ������ȫʧ������ֻ�ܺ���Ƚ���");
		return notify_fail("��������̫�岢������������\n");
	}

	command("heng");
	command("say ���аɣ�");
	message_vision(HIY "$N����δ�䣬����һ���������񽣶�׼$n" HIY
			   "����бб�̳����������صմ������ǽ�����"NOR"\n",
			   obj, this_player());

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
		message_vision(CYN "\n����������üͷ������������������"NOR"\n",
				   this_object());

		query("anti")->set_temp("win_he",1);
		query("anti")->delete_temp("bi");
	}
::die();
}

