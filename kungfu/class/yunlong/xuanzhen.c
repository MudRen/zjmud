// xuanzhen.c �������

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("�������", ({ "xuan zhen", "xuan", "zhen" }));
	set("gender", "����");
	set("title", HIR "��ػ�"HIG"��ľ��"NOR"����");
	set("long", "\n��λ��Ĭ���Եĵ��ˣ�������ػ���ľ�û�����\n"+
		"������ľ����һ�����ĺ��֣�һ������ʹ�ó����뻯��\n");
	set("age", 55);
	set("class", "taoist");
	set("int", 30);
	
	set("qi", 2800);
	set("max_qi", 2800);
	set("jing", 1200);
	set("max_jing", 1200);
	set("shen_type", 1);

	set("combat_exp", 100000);
	set("attitude", "friendly");

	set_skill("force", 80);
	set_skill("unarmed", 80);
	set_skill("parry", 80);
	set_skill("dodge", 80);
	set_skill("sword", 100);
	set_skill("whip", 80);
	set_skill("hand", 70);
	set_skill("claw", 70);
	set_skill("yunlong-shengong", 70);
	set_skill("yunlong-shenfa", 70);
	set_skill("yunlong-xinfa", 70);
	set_skill("yunlong-bian", 70);
	set_skill("yunlong-jian", 80);
	set_skill("yunlong-shou", 50);
	set_skill("yunlong-zhua", 50);
	set_temp("apply/attack", 70);
	set_temp("apply/defense", 70);
	set_temp("apply/damage", 60);

	map_skill("force", "yunlong-shengong");
	map_skill("dodge", "yunlong-shenfa");
	map_skill("parry", "yunlong-jian");
	map_skill("sword", "yunlong-jian");
	map_skill("hand", "yunlong-shou");
	map_skill("claw", "yunlong-zhua");
	map_skill("whip", "yunlong-bian");

	prepare_skill("hand", "yunlong-shou");
	prepare_skill("claw", "yunlong-zhua");
	create_family("������",2, "����");
	set("book_count", 1);

	set("inquiry", ([
		"�½���" : "����ܶ����ɲ����װ���",
		"��ػ�" : "ֻҪ��Ӣ�ۺú���������������ػᡣ",
		"���帴��" : "ȥ�ײĵ�ͻش�����ϸ���ưɣ�",
		"����" : "�����£�",
		"�п�" : "�����£�",
	]));

	set("chat_chance_combat", 50);  
	set("chat_msg_combat", ({
		(: command("smile") :),
		(: command("haha") :),
		(: command("chat ��λ" + RANK_D->query_respect(this_player()) + "��������ԩ�޳𣬺α���ˣ�") :),
		(: command("unwield changjian") :),
		(: command("unwield changjian") :),
		(: command("unwield changjian") :),
		(: command("unwield changjian") :),
		(: command("unwield changjian") :),
		(: command("unwield changjian") :),
		(: command("unwield changjian") :),
		(: command("unwield changjian") :),
		(: command("wield changjian") :),
		(: command("wield changjian") :),
		(: command("wield changjian") :),
		(: command("wield changjian") :),
		(: command("wield changjian") :),
		(: command("wield changjian") :),
		(: command("wield bian") :),
		(: command("wield bian") :),
		(: command("wield bian") :),
		(: command("wield bian") :),
		(: perform_action, "sword.xian" :),
		(: perform_action, "sword.xian" :),
		(: perform_action, "sword.xian" :),
		(: perform_action, "whip.chan" :),
		(: perform_action, "whip.chan" :),
		(: exert_function, "recover" :),
		(: exert_function, "recover" :),
		(: command("unwield bian") :),
		(: command("unwield bian") :),
		(: command("unwield bian") :),
		(: command("unwield bian") :),
		      }) );
	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 12);
}

void init()
{
	::init();
	add_action("do_join", "join");
}

#include "/kungfu/class/yunlong/tiandihui.h"
