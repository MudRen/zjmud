#include <ansi.h>
inherit NPC;

void create()
{
	set_name("�ױ���", ({ "he biweng", "he", "biweng" }));
	set("long", "һ����ʮ��������ߣ�ͷ�����ף������⣬\n"
		    "��Ŀ���ߴ���������������ؽ�Ƹ���\n"
		    "���֣���ڤ�����еĺױ��̣�һ˫��ڤ����\n"
		    "ʹ�ó����뻯�����ճ�Ⱥ���ܵ�����������\n"
		    "ʶ��\n");
	set("title", MAG "��ڤ����" NOR);
	set("gender", "����");
	set("age", 68);
	set("attitude", "peaceful");
	set("shen_type", -1);

	set("per", 30);
	set("str", 40);
	set("int", 40);
	set("con", 40);
	set("dex", 40);
	
	set("max_qi", 6000);
	set("max_jing", 2100);
	set("neili", 10000);
	set("max_neili", 6800);
	set("jiali", 250);
	set("combat_exp", 2800000);

	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: perform_action, "strike.wuji" :),
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
	}) );

	set_skill("literate", 100);
	set_skill("force", 270);
	set_skill("dodge", 250);
	set_skill("unarmed", 270);
	set_skill("parry", 270);
	set_skill("strike", 280);
	set_skill("lingxu-bu", 250);
	set_skill("xuanming-zhang", 280);
	set_skill("xuanming-shengong", 270);

	map_skill("dodge", "lingxu-bu");
	map_skill("force", "xuanming-shengong");
	map_skill("strike", "xuanming-zhang");
	map_skill("parry", "xuanming-zhang");

	prepare_skill("strike", "xuanming-zhang");

	setup();
	carry_object("/clone/cloth/cloth")->wear();
}
