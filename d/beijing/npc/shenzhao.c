inherit NPC;
#include <ansi.h>
inherit F_MASTER;
void create()
{
	set_name("��������", ({ "shen zhao","shen","zhao",}));
	set("long","����һλͺ����ɮ����һϮ��ɫ������ġ�\n"
		"������Ըߣ�̫��Ѩ΢͹��˫Ŀ��������\n"
	);
	set("gender", "����");
	set("title", "������������ͷ��");
	set("attitude", "friendly");
	set("class", "bonze");
	set("age", 50);
	set("shen_type", 0);
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set("max_qi", 900);
	set("max_jing", 500);
	set("neili", 800);
	set("max_neili", 800);
	set("jiali", 50);
	set("combat_exp", 80000);
	set("score", 100);

	set_skill("force", 80);
	set_skill("hunyuan-yiqi", 80);
	set_skill("dodge", 80);
	set_skill("shaolin-shenfa", 80);
	set_skill("cuff", 80);
	set_skill("jingang-quan", 80);
	set_skill("unarmed", 80);
	set_skill("parry", 80);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("cuff", "jingang-quan");
	prepare_skill("cuff", "jingang-quan");
	setup();
	carry_object("/d/beijing/npc/obj/jiasha")->wear();
}
