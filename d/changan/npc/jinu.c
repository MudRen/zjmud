//jinu.c

inherit NPC;

#include <ansi.h>
#include "bajiao.h"

void create()
{
	set_name("��Ů", ({ "ji nu" }) );
	set("gender", "Ů��" );
	set("age", 25);
	set("str", 10);
	set("per", 30);
	set("combat_exp", 10);
	set("attitude", "friendly");

	setup();
}

