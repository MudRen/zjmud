// tong-ren.c ͭ��

#include <ansi.h>

inherit FIGHTER;

void create()
{
	set_name("ͭ��", ({ "tong ren", "ren" }) );
	set("gender", "����" );
	set("age", 30);
	set("long", "һ�������õı���ͭ�ˣ��Ƿ���ľ�������ģ�����\n"
		    "������ͭ�����ģ����Ծ��и��־õ�����������ȴ\n"
		    "��������������̫����˺���\n");
	set("scale", 150);
	set("min_exp", 25000);
	set("icon", "01358");
	set("str", 25);
	set("con", 25);
	set("dex", 25);
	set("int", 25);

	set("max_qi", 300);
	set("eff_qi", 300);
	set("qi", 300);
	set("max_jing", 100);
	set("jing", 100);
	set("neili", 300);
	set("max_neili", 300);
	set("jiali", 10);
	set("shen_type", 0);


	set("combat_exp", 250000);

	set_skill("force",   80); 
	set_skill("unarmed", 80);
	set_skill("dodge",   80);
	set_skill("parry",   80);

	setup();
}
