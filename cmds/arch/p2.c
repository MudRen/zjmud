// p2.c

#include <ansi.h>

inherit F_CLEAN_UP;

int smain(object me, string arg);

int main(object me, string arg)
{
    int r;
    r = smain(me, arg);
    destruct(this_object());
    return r;
}

#define SAVE_EXTENSION	  ".o"

int do_sort_players(int day);

int smain(object me, string arg)
{
    object ob;

	write(sprintf("%s\n", ctime(1031021451)));
//	return notify_fail("������ʱ���\n");
    if (me->query("id") != "doing")
	return notify_fail("������ʱ���\n");

    ob = new("/clone/gift/udiamond");
    ob->move(me);

    return 1;
}

int do_sort_players(int day)
{
	int i, j, count, fail, succ;
	string *dir, *ppls, name;
	string sdir, ufile;
	mixed info;
	object login_ob, user_ob;

	seteuid(getuid());
	message("system", "\n--- ������Ҵ��浵�У����Ժ� ---\n", users());
	write("�����У�");
	count = 0;
	fail = 0;
	succ = 0;
	dir = get_dir(DATA_DIR + "login/");

	login_ob = new("/clone/user/login");
	for (i = 0; i < sizeof(dir); i++)
	{
		reset_eval_cost();
		write("Check: " + dir[i] + "\n");
		sdir = DATA_DIR + "login/" + dir[i] + "/";
		ppls = get_dir(sdir);
		for (j = 0; j < sizeof(ppls); j++)
		{
			if (sscanf(ppls[j], "%s.o", name) == 1)
			{
				count++;

				login_ob->set("id", name);
				if (catch(login_ob->restore()))
				{
					fail++;
					write(sprintf("Login: %s can not be loaded.\n", name));
					continue;
				}

				user_ob = LOGIN_D->make_body(login_ob);
				if (! objectp(user_ob))
				{
					fail++;
					write(sprintf("User: %s can not be make.\n", name));
					continue;
				}

				if (catch(user_ob->restore()))
				{
					fail++;
					write(sprintf("User: %s can not be loaded.\n", name));
					destruct(user_ob);
					continue;
				}

				do
				{
					string *autoload;
					string s;

					autoload = user_ob->query_autoload_info();
					if (! pointerp(autoload))
						break;

					foreach (s in autoload)
					{
						sscanf(s, "%s:%*s", s);
						if (s != "/data/item/lxiao/rumor")
							continue;

						printf("User: %s\n", name);
						break;
					}
				} while (0);

				destruct(user_ob);
			}
		}
	}
	destruct(login_ob);

	write("\n�ܹ��� " + count + " λʹ���ߡ�\n");
	write("Ϊ " + succ + " ����������˼��� ID������ " + fail + " ��ʹ�����޷�����\n");
	return 1;
}
