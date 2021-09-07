// bencan.c

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("����", ({ "ben can","can"}) );
	set("gender", "����" );
	set("long", "����Ŀ�ΰ��Ϊ�����ɵ�ʦ�֡�\n" );
	set("title", "�����µ�ʮ�ߴ�ɮ��");
	set("class", "bonze");
	set("age", 49);
	set("shen_type", 1);
	set("str", 25);
	set("int", 24);
	set("con", 22);
	set("dex", 23);

	set("qi", 3200);
	set("max_qi", 3200);
	set("jing", 1600);
	set("max_jing", 1600);
	set("neili", 4500);
	set("max_neili", 4500);
	set("jiali", 50);
	set("combat_exp", 1250000);

	set_skill("force", 220);
	set_skill("dodge", 210);
	set_skill("parry", 210);
	set_skill("finger", 220);
	set_skill("sword", 210);
	set_skill("tiannan-step", 210);
	set_skill("duanshi-xinfa", 220);
	set_skill("duanjia-sword", 210);
	set_skill("sun-finger", 220);
	set_skill("buddhism", 140);
	set_skill("literate", 60);

	set("inquiry" ,([
		"��������" : "�ߣ�\n",
		"������" :  "�ߣ�\n",
	]));

	map_skill("force", "duanshi-xinfa");
	map_skill("dodge", "tiannan-step");
	map_skill("parry", "sun-finger");
	map_skill("finger", "sun-finger");
	map_skill("sword", "duanjia-sword");
	prepare_skill("finger","sun-finger");
	create_family("����μ�", 15, "��ɮ");
	setup();
	carry_object("/d/xueshan/obj/b-jiasha")->wear();
}

#include "ben.h"
