// shaolin ������ʮ������

#include <ansi.h>

inherit SKILL;

int is_shaolin_skill() { return 1; }

string this_skill()
{
	string sk;
	sscanf(base_name(this_object()), "/kungfu/skill/%s", sk);
	return sk;
}
