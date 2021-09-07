
#include <ansi.h>
#include <login.h>
#include <command.h>

inherit ROOM;

int is_chat_room() { return 1; }

int do_wash(string arg);
int do_washto(string arg);
int do_born(string arg);
int do_pianshu(string arg);

mapping born = ([
	"��������" : "/d/guanwai/kedian",
	"��������" : "/d/beijing/kedian",
	"��³����" : "/d/taishan/kedian",
	"�ؽ�����" : "/d/changan/kezhan",
	"��ԭ����" : "/d/shaolin/kedian1",
	"��������" : "/d/xingxiu/kedian",
	"��������" : "/d/xiangyang/kedian",
	"��������" : "/d/city/kedian",
	"��������" : "/d/suzhou/kedian",
	"��������" : "/d/hangzhou/kedian",
	"��������" : "/d/fuzhou/kedian",
	"��������" : "/d/city3/kedian",
	"��������" : "/d/dali/kedian",
	"��������" : "/d/foshan/beidimiao",
	"ŷ������" : ([ "born"      : "��������",
			"surname"   : "ŷ��",
			"startroom" : "/d/baituo/dating",
		     ]),
	"�������" : ([ "born"      : "��������",
			"surname"   : "��",
			"startroom" : "/d/guanwai/xiaowu",
		     ]),
	"���ϻ���" : ([ "born"      : "��������",
			"surname"   : "��",
			"startroom" : "/d/dali/wangfugate",
		     ]),
	"Ľ������" : ([ "born"      : "��������",
			"surname"   : "Ľ��",
			"startroom" : "/d/yanziwu/cuixia",
		     ]),
]);

void create()
{
	int i, k;
	string desc;
	string *position;

	set("short", HIR "���޵�" NOR);
	set("long", @LONG
��������ֲ������˸о���һ����ĺ��⣬��������ţͷ���棬ڤ
�����䣬�����������¡�ʮ�����ޣ������ڴˣ��ز������ڴ���֮�ϣ�
��ŭ����������ȽŲ�������Щ���ˡ�
    ��������һ��ʯͷ���ɵĳ��ӣ�����ˮ�峺ȴ�����ף���֪����
�����ж��
    �Ա��м������ӣ���Ҳ��Ӧ����ϸ������
LONG );
	set("no_fight", 1);

	set("objects", ([
		__DIR__"npc/dizangwang" : 1,
	]));

	set("no_say", "���޵�����ɭ�ֲ������������˵����\n");


	setup();
}

