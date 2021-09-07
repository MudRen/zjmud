// benxiang.c

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("����", ({ "ben xiang","xiang"}) );
	set("gender", "����" );
	set("long", "һ���ݻƾ��ݵ�ɮ�ˣ����Ǳ����ɵ�ʦ�֡�\n");
	set("title", "�����µ�ʮ�ߴ�ɮ��");
	set("class", "bonze");
	set("age", 50);
	set("shen_type", 1);
	set("str", 22);
	set("int", 26);
	set("con", 24);
	set("dex", 23);

	set("qi", 3500);
	set("max_qi", 3500);
	set("jing", 1700);
	set("max_jing", 1700);
	set("neili", 4400);
	set("max_neili", 4400);
	set("jiali", 50);
	set("combat_exp", 1400000);

	set_skill("force", 230);
	set_skill("dodge", 210);
	set_skill("parry", 230);
	set_skill("finger", 230);
	set_skill("sword", 210);
	set_skill("tiannan-step", 210);
	set_skill("duanshi-xinfa", 230);
	set_skill("duanjia-sword", 210);
	set_skill("sun-finger", 230);
	set_skill("buddhism", 150);
	set_skill("literate", 100);

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
