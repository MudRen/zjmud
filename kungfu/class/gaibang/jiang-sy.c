// jiang-shangyou.c
inherit NPC;
inherit F_MASTER;

#include "gaibang.h"

void create()
{
	set_name("������", ({"jiang shangyou", "jiang", "shangyou"}));
	set("title", "ؤ���������");
	set("gender", "����");
	set("age", 19);
	set("long",
		"����λؤ��������ӣ������Ǹ�Ӣ�����\n");
	set("attitude", "peaceful");
	set("class", "beggar");
	set("str", 25);
	set("int", 20);
	set("con", 20);
	set("dex", 27);
	set("max_qi", 300);
	set("max_jing", 200);
	set("neili", 900);
	set("max_neili", 900);
	set("jiali",25);
	set("combat_exp", 110000);
	set_skill("force", 90);
	set_skill("jiaohua-neigong", 90);
	set_skill("unarmed", 50);
	set_skill("changquan", 50);
	set_skill("dodge", 50);
	set_skill("feiyan-zoubi", 50);
	set_skill("parry", 90);
	set_skill("begging", 50);
	set_skill("checking", 40);
	map_skill("force", "jiaohua-neigong");
	map_skill("unarmed", "changquan");
	map_skill("dodge", "feiyan-zoubi");
	create_family("ؤ��", 20, "����");
	setup();
}
