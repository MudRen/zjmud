#include <ansi.h>
inherit NPC;
void create()
{
	set_name("�׹���", ({ "bai guishou", "bai", "guishou"}) );
	set("long", "һ����ʮ��������ߣ�ͺ��ͷ����һ���ʵ�ļ��⡣\n");
	set("attitude", "heroism");
	set("title", "��ӥ��");
	set("nickname", HIW "����̳̳��" NOR);
	set("combat_exp", 500000);
	set("age", 50);
	set("chat_chance_combat", 2);
	set("chat_msg_combat", ({
		"�׹��ٺȵ����޳�С�������Ҵ������������⣿\n",
	}) );
	set_skill("force", 100+random(60));
	set_skill("hunyuan-yiqi", 100+random(60));
	set_skill("dodge", 100+random(60));
	set_skill("shaolin-shenfa", 100+random(60));
	set_skill("finger", 100+random(60));
	set_skill("nianhua-zhi", 100+random(60));
	set_skill("parry", 100+random(60));

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("finger", "nianhua-zhi");
	map_skill("parry", "nianhua-zhi");

	set_temp("apply/attack", 50+random(50));
	set_temp("apply/defense", 50+random(50));
	set_temp("apply/armor", 50+random(50));
	set_temp("apply/damage", 50+random(50));

	setup();

	carry_object("/d/tulong/tulong/npc/obj/jiaofu")->wear();
}

