// swmuding.c ��ľ����

#include <ansi.h>

inherit "/clone/misc/muding";

mapping insects = ([
	"zhizhu"	: 10000,
	"chanchu"       : 10000,
	"xiezi"	 : 10000,
	"wugong"	: 10000,
	"duzhu"	 : 35000,
	"huoxie"	: 35000,
	"jinwugong"     : 35000,
	"heiguafu"      : 20000,
	"wucaizhu"      : 15000,
	"ciwugong"      : 15000,
	"bihuochan"     : 15000,
	"xuexi"	 : 15000,
	 "bingcan"       : 500,
]);

void create()
{
	set_name(YEL "��ľ����" NOR, ({"shenmu wangding", "mu ding", "muding", "ding"}) );
	set_weight(1200);
	set("long", @LONG
һֻ�ƲӲӵ�ľ�ƵĶ�������ȥ�ио���Щ���أ�ϸ����ȴ��һ����ζ��������ζ�С�
LONG );
	set("unit", "ֻ");
	set("value", 50000);
	set("no_sell", 1);
	set_max_encumbrance(700);
	setup();
}
