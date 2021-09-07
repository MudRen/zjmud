//Room: qunyulou.c

#include <ansi.h>

inherit ROOM;

int check_container(object ob);

void create()
{
	set("short", "Ⱥ��¥");
	set("long", 
"Ⱥ��¥�ǳ���������һָ�Ĵ��Ժ�����ﲻ����ͨ�������ĵط���\n"
"����㲻�Ǹ���һ���Ĳ���������㲻���۰�һ���İ������ţ������\n"
"�����������壬�����������Ҳ���롣¥�й͵Ĵ��ֱ��������������\n"
"�ţ�������ͷ�����ļ�������������ƿ���ȥ���������Ÿ�ʾ(gaoshi)\n"
"һ�ţ��ָ߹�����������\n"
HIR"	     ��"HIG"	      ��\n"NOR"\n"
HIR"	     ��"HIG"	      ɫ\n"NOR"\n"
HIR"	     ʴ"HIG"	      ��\n"NOR"\n"
HIR"	     ��"HIG"	      ��"NOR"\n"  	
	);
	set("exits", ([ /* sizeof() == 2 */
		"north" : __DIR__"qixiang4",
		"south" : __DIR__"qunyulou1",
	]));
	set("item_desc", ([
		"gaoshi": HIY @TEXT
�涨:
���������Դ�������¥��
�����������£��������Ը���
TEXT NOR
	]) );
	set("objects", ([
		__DIR__"npc/dashou" : 4,
	]) );

	set("NONPC",1);
	setup();
}

int valid_leave(object me, string dir)
{    
	object ob;
	object *inv;
	int i;
	if (dir == "south" &&
	    objectp(ob = present("da shou", this_object())) &&
	    living(ob))
	{
		if (wizardp(me))
			return ::valid_leave(me, dir);

		if ((string)me->query("gender")=="Ů��")
			return notify_fail(ob->name() +
			       "һ��ץס���㣬˵��:�����ﲻ��Ů��"
			       "�����ĵط�������ȥ����\n");
		inv = all_inventory(me);
		for(i = 0; i < sizeof(inv); i++)
		{
			if ((int)inv[i]->query("weapon_prop"))
				return notify_fail(ob->name() +
						   "һ��ץס���㣬˵������������������"
						   "��صĵط�����׼���������롣��\n");
		}
	}
	return 1;
}
